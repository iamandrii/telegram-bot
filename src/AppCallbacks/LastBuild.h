#pragma once

#include <bits/stdc++.h>
#include <tgbot/tgbot.h>
#include "../AppMessages/Messages.h"
#include <boost/log/trivial.hpp>
#include "../AppConfig/Config.h"
#include "../AppHandlersEngine/HandlersEngine.h"
using namespace std;
namespace App{
	namespace Callbacks{
		class LastBuild : public App::HandlersEngine::AbstractCallback{
		private:
			const char* code = "lastbuild";
		public:
			LastBuild(){};
			pair<App::HandlersEngine::Matcher, function<void(TgBot::Bot, App::Event *)>> operator()() {
				return {
					App::HandlersEngine::Matcher(this->code, regex("/lastbuild(@.*)?")), 
					[](TgBot::Bot bot, App::Event *event) {
						BOOST_LOG_TRIVIAL(debug) << "LastBuild parsing...";
						App::Message::Forward(App::Message::Parameters(event), App::Message::ForwardParameters(
								event->getConfig()->get<long long>("news_channel"),
								event->getConfig()->get<long long>("news_last_message"))).send(bot);
					}
				};
			}
		};
	}
}