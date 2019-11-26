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
		class Triggered : public App::HandlersEngine::AbstractCallback{
		private:    
			const char* code = "triggered";
		public:
			Triggered(){};
			pair<App::HandlersEngine::Matcher, function<void(TgBot::Bot, App::Event *)>> operator()() {
				return {
					App::HandlersEngine::Matcher(this->code, regex("/triggered(@.*)?")), 
					[](TgBot::Bot bot, App::Event *event) {
						BOOST_LOG_TRIVIAL(debug) << "Triggered parsing...";
						App::Message::Sticker(event->getConfig()->get<string>("triggered_sticker"),
										App::Message::Parameters(event, true)).send(bot);
				}};
			}
		};
	}
}