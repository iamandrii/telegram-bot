#pragma once

#include <bits/stdc++.h>
#include <tgbot/tgbot.h>
#include <boost/log/trivial.hpp>
#include "../AppMessages/Messages.h"
#include "../AppHandlersEngine/HandlersEngine.h"
#include "../AppEvent/Event.h"
using namespace std;
namespace App{
	namespace Callbacks{
		class SaveIt : public App::HandlersEngine::AbstractCallback{
		private:    
			const char* code = "saveit";
		public:
			SaveIt(){};
			pair<App::HandlersEngine::Matcher, function<void(TgBot::Bot, App::Event *)>> operator()() {
				return {
					App::HandlersEngine::Matcher(this->code, regex("/saveit(@.*)?")),
					[](const TgBot::Bot &bot, App::Event *event) {
						BOOST_LOG_TRIVIAL(debug) << "SaveIt parsing...";
						if (event->getMessage()->replyToMessage != nullptr) {
							App::Message::Forward(App::Message::Parameters(
									event->getConfig()->get<long long>("fame_chat_id")).setDisableWebPagePreview(
									true), App::Message::ForwardParameters(
									event->getMessage()->replyToMessage)).send(bot);
							App::Message::Text("now you are popular! check at " +
											   event->getConfig()->get<string>("fame_chat_link"),
											   App::Message::Parameters(event, true)).send(bot);
						} else {
							App::Message::Text(
									"you must sent /saveit as reply to message which you want to save forever",
									App::Message::Parameters(event, true)).send(bot);
						}
					}
				};
			}
		};
	}
}