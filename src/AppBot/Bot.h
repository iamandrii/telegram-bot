#include <bits/stdc++.h>

#include <tgbot/tgbot.h>
#include "../AppConfig/Config.h"
#include "../AppMessages/Messages.h"
#include "../AppHandlersEngine/HandlersEngine.h"
#include "../AppEvent/Event.h"

using namespace std;

namespace App{
	class Bot{
	private:
		bool stopf = false;
		bool skipnext = false;
		App::Config* config;
		string token;
		App::HandlersEngine::Handler* handler;
	public:
		Bot(App::Config* config, App::HandlersEngine::Handler* handler, bool dev = false);
		void start();
		void stop();
	};
}
