#pragma once

#include <bits/stdc++.h>
#include <tgbot/tgbot.h>
#include <boost/log/trivial.hpp>
#include "../AppHandlersEngine/HandlersEngine.h"
#include "../AppMessages/Messages.h"
#include "../AppConfig/Config.h"
using namespace std;
namespace App{
	namespace Callbacks{
		class Summon : public App::HandlersEngine::AbstractCallback{
		private:	
			const char* code = "summon";
		public:
			Summon(){};
			pair<App::HandlersEngine::Matcher, function<void(TgBot::Bot, App::Event *)>> operator()() {
				return {
					App::HandlersEngine::Matcher(this->code, regex("/summon(@.*)?")), 
					[](TgBot::Bot bot, App::Event *event) {
						BOOST_LOG_TRIVIAL(debug) << "Summon parsing...";
						if (event->getMessage()->replyToMessage != nullptr) {
							if (event->getMessage()->replyToMessage->from->username != "") {
								App::Message::Text("@" + event->getMessage()->replyToMessage->from->username,
												   App::Message::Parameters(event)).send(bot);
							} else {
								stringstream ss;
								ss << "<a href=\"tg://user?id=";
								ss << event->getMessage()->replyToMessage->from->id;
								ss << "\">";
								ss << event->getMessage()->replyToMessage->from->firstName;
								ss << "</a>";
								App::Message::Text(ss.str(), App::Message::Parameters(event).setParseMode("HTML")).send(
										bot);
							}
						} else {
							App::Message::Text("@xhzgk", App::Message::Parameters(event)).send(bot);
						}
				}};
			}
		};
	}
}
