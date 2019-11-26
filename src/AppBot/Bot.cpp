#include <bits/stdc++.h>
#include <boost/log/trivial.hpp>

#include "Bot.h"

#include <tgbot/tgbot.h>
#include <chrono>
#include "../AppConfig/Config.h"
#include "../AppMessages/Messages.h"
#include "../AppHandlersEngine/HandlersEngine.h"
#include "../AppEvent/Event.h"

using namespace std;

using namespace App;

Bot::Bot(App::Config* config, App::HandlersEngine::Handler* handler, bool dev){
	if(!dev) this->token = config->get<string>("token");
	else this->token = config->get<string>("dev_token");
	this->config = config;
	this->handler = handler;
	BOOST_LOG_TRIVIAL(info) << "Token: " << token;
}

void Bot::start(){
	TgBot::Bot bot(this->token);
	BOOST_LOG_TRIVIAL(info) << "bot object created";
	auto* db = new App::Database::Database(this->config);
	bot.getEvents().onAnyMessage([&](TgBot::Message::Ptr message) {
		if(message->text.empty() || message->chat->type == TgBot::Chat::Type::Private) return; 
		BOOST_LOG_TRIVIAL(info) << "N: " << message->chat->id << "(" << message->chat->title << ")/" << message->from->id << "(" << message->from->firstName << "): " << message->text.c_str();
		if(this->skipnext){
			this->skipnext = false;
			BOOST_LOG_TRIVIAL(info) << "skipping";
			return;
		}

		auto* user = new App::User(message->from->id, message->from->firstName, message->from->username);
		BOOST_LOG_TRIVIAL(debug) << "sender: " << user->dump();
		user->setDB(db)->sync_up();

		auto* group = new App::Group(message->chat->id, message->chat->title);
		BOOST_LOG_TRIVIAL(debug) << "at group: " << group->dump();
		group->setDB(db)->sync_up()->connectUser(user);

		auto* event = new App::Event(message, db, config, user, group);
		BOOST_LOG_TRIVIAL(debug) << "created event";

		try{
			handler->handle(bot, event);
			BOOST_LOG_TRIVIAL(debug) << "handled ok";
			return;
		}catch(exception& e){
			BOOST_LOG_TRIVIAL(error) << "handling error:" << e.what();
		}
	});
	try {
		BOOST_LOG_TRIVIAL(info) << "username: @" << bot.getApi().getMe()->username;
		bot.getApi().deleteWebhook();
		TgBot::TgLongPoll longPoll(bot);
		while (!this->stopf) {
			BOOST_LOG_TRIVIAL(debug) << "longpoll (re-)started";
			longPoll.start();
		}
	} catch (exception& e) {
		BOOST_LOG_TRIVIAL(error) << "runtime error: " << e.what();
		this->skipnext = true;
		this->start();
	}
};

void Bot::stop(){
	BOOST_LOG_TRIVIAL(debug) << "executed stop";
	this->stopf = true;
};
