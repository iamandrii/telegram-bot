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
		class CleanUpTo : public App::HandlersEngine::AbstractCallback {
		private:
			const char* code = "cleanupto";
		public:
			CleanUpTo() {};

			pair<App::HandlersEngine::Matcher, function<void(TgBot::Bot, App::Event *)>> operator()() {
				return {
					App::HandlersEngine::Matcher(this->code, regex("/cleanupto(@.*)?")), 
					[](TgBot::Bot bot, App::Event *event) {
						BOOST_LOG_TRIVIAL(debug) << "CleanUpTo parsing...";
						if (event->getMessage()->replyToMessage == nullptr) {
							App::Message::Text(
									"you must send /cleanupto as a reply to message, from which you want to clean chat.",
									App::Message::Parameters(event, true)).send(bot);
						} else {
							bool deletedAtLeastOne = false;
							for (long long i = event->getMessage()->replyToMessage->messageId + 1;
								 i <= event->getMessage()->messageId; i++) {
								bool ok = true;
								try {
									bot.getApi().deleteMessage(event->getMessage()->chat->id, i);
								} catch (TgBot::TgException &e) {
									ok = false;
								}
								deletedAtLeastOne |= ok;
							}
							if (!deletedAtLeastOne) {
								App::Message::Text("can't do it. have i admin rights?",
												   App::Message::Parameters(event)).send(bot);
							}
						}
					}
				};
			}
		};
	}
}
