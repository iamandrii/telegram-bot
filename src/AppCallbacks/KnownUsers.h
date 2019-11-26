#pragma once

#include <bits/stdc++.h>
#include <tgbot/tgbot.h>
#include <boost/log/trivial.hpp>
#include "../AppMessages/Messages.h"
#include "../AppConfig/Config.h"
#include "../AppHandlersEngine/HandlersEngine.h"
#include "../AppUser/User.h"
#include "../AppGroup/Group.h"
using namespace std;
namespace App{
	namespace Callbacks{
		class KnownUsers : public App::HandlersEngine::AbstractCallback {
		private:
			const char* code = "knownusers";
		public:
			KnownUsers() {};

			pair<App::HandlersEngine::Matcher, function<void(TgBot::Bot, App::Event *)>> operator()() {
				return {
					App::HandlersEngine::Matcher(this->code, regex("/dbknownusers(@.*)?")),
					[](TgBot::Bot bot, App::Event *event) {
						BOOST_LOG_TRIVIAL(debug) << "KnownUsers parsing...";
						vector<App::User *> *users = event->getGroup()->listUsers();
						stringstream ss;
						for (unsigned long long i = 0; i < users->size(); i++) {
							ss << i + 1;
							ss << ": ";
							ss << (*users)[i]->first_name;
							ss << " @";
							ss << (*users)[i]->username;
							ss << " ;\n";
						}

						App::Message::Text(ss.str(), App::Message::Parameters(event, true)).send(bot);
					}
				};
			}
		};
	}
}