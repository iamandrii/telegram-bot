#include "../Messages.h"

#include <boost/log/trivial.hpp>
#include <bits/stdc++.h>
#include <tgbot/tgbot.h>
#include "../../AppExceptions/Exceptions.h"

using namespace std;

using namespace App;

Message::Text::Text(string text, App::Message::Parameters params) :
    text(text),
    params(params) {};

void Message::Text::send(TgBot::Bot bot){
    if(this->params.to_chat == -1) throw App::Exceptions::UndefinedVariableError("Parameters.to_chat is undefined");
    bot.getApi().sendMessage(this->params.to_chat, this->text, this->params.disable_web_page_preview, this->params.reply_to, make_shared<TgBot::GenericReply>(), this->params.parse_mode, this->params.silent);
    BOOST_LOG_TRIVIAL(debug) << "sent text message";
	BOOST_LOG_TRIVIAL(debug) << '\t' << "params " << this->params.dump();
	BOOST_LOG_TRIVIAL(debug) << '\t' << "text " << this->text;
}