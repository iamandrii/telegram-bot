#define BOOST_LOG_DYN_LINK 1
#include <bits/stdc++.h>
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
using namespace std;

#include "AppExceptions/Exceptions.h"
#include "AppCallbacks/_IncludeAll.h"
#include "AppHandlersEngine/HandlersEngine.h"
#include "AppBot/Bot.h"

bool is_command(char *buffer, string wh){
	bool res = 1;
	for(unsigned int i = 0;i<wh.length();i++) res = res & (wh[i] == buffer[i]);
	return res;
}

void init_logging(App::Config* config){
		 if(config->get<string>("loglevel") == "trace") boost::log::core::get()->set_filter(boost::log::trivial::severity >= boost::log::trivial::trace);
	else if(config->get<string>("loglevel") == "debug") boost::log::core::get()->set_filter(boost::log::trivial::severity >= boost::log::trivial::debug);
	else if(config->get<string>("loglevel") == "info") boost::log::core::get()->set_filter(boost::log::trivial::severity >= boost::log::trivial::info);
	else if(config->get<string>("loglevel") == "warning") boost::log::core::get()->set_filter(boost::log::trivial::severity >= boost::log::trivial::warning);
	else if(config->get<string>("loglevel") == "error") boost::log::core::get()->set_filter(boost::log::trivial::severity >= boost::log::trivial::error);
	else if(config->get<string>("loglevel") == "fatal") boost::log::core::get()->set_filter(boost::log::trivial::severity >= boost::log::trivial::fatal);
	else throw App::Exception("attributes error");
}

void killbot(bool& working, thread& t1, long long& nat_hand){
	if(working){
        BOOST_LOG_TRIVIAL(info) << "killing bot";
		t1.detach();
		pthread_cancel(nat_hand);
		working = false;
	}
}

void startbot(bool& working, thread& t1, long long& nat_hand, App::Bot& bot){
    if(!working){
        BOOST_LOG_TRIVIAL(info) << "starting bot";
        t1 = thread([&](){
            bot.start();
        });
        working = true;
        nat_hand = t1.native_handle();
    }
}

bool in_shell = false;
bool dev = false;

int main(int argc, char **argv) {

    auto* handlers = new App::HandlersEngine::Handler();

    auto* config = new App::Config();

	for(int i = 1;i<argc;i++){
		smatch match;
		string str = string(argv[i]);
		if(regex_match(str, match, regex("--in-shell")) == true) in_shell = true;
		if(regex_match(str, match, regex("--dev")) == true) dev = true;
		if(regex_match(str, match, regex("--config:([A-Za-z0-9_]+)=([0-9_]+)")) == true) config->set(match.str(1).c_str(), atoi(match.str(2).c_str()));
		if(regex_match(str, match, regex("--config:([A-Za-z0-9_]+)=([A-Za-z0-9_]+)")) == true) config->set(match.str(1).c_str(), match.str(2).c_str());
		if(regex_match(str, match, regex("--config:([A-Za-z0-9_]+)=\"(.*)\"")) == true) config->set(match.str(1).c_str(), match.str(2).c_str());
	}

	init_logging(config);


	BOOST_LOG_TRIVIAL(debug) << "arguments parsed";

	handlers->register_callback(App::Callbacks::LastBuild()());
	handlers->register_callback(App::Callbacks::Summon()());
	handlers->register_callback(App::Callbacks::Triggered()());
	handlers->register_callback(App::Callbacks::KnownUsers()());
	handlers->register_callback(App::Callbacks::RandomProblem()());
	handlers->register_callback(App::Callbacks::SaveIt()());
	handlers->register_callback(App::Callbacks::CleanUpTo()());

    BOOST_LOG_TRIVIAL(debug) << "handlers loaded";

	signal(SIGINT, [](int s) {
        BOOST_LOG_TRIVIAL(fatal) << "got sigint";
		exit(0);
	});

    App::Bot bot{config, handlers, dev};

	bool working = false;
	long long nat_hand = -1;
	thread t1 = thread([&](){
		bot.start();
	});
	working = true;
	nat_hand = t1.native_handle();

	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in address{};
	socklen_t address_length= sizeof(sockaddr_in);
	address.sin_family = AF_INET; 
	address.sin_addr.s_addr = INADDR_ANY; 
	address.sin_port = htons(64355);
	bind(sockfd, (struct sockaddr *)&address, sizeof(address));
	listen(sockfd, 3);
	int new_socket;
	while((new_socket = accept(sockfd, (struct sockaddr *)&address, (socklen_t*)&address_length))){
        BOOST_LOG_TRIVIAL(info) << "received command";
		char buffer[1024] = {0};
		read(new_socket, buffer, 1024);
		if(is_command(buffer, "start")){
            BOOST_LOG_TRIVIAL(debug) << "command 'start'";
            startbot(working, t1, nat_hand, bot);
		}else if (is_command(buffer, "stop")){
            BOOST_LOG_TRIVIAL(debug) << "command 'stop'";
			killbot(working, t1, nat_hand);
		}else if (is_command(buffer, "status")){
            BOOST_LOG_TRIVIAL(debug) << "command 'status'";
			send(new_socket, (working ? "running" : "stopped"), 7, 0);
		}else if(is_command(buffer, "restart")){
            BOOST_LOG_TRIVIAL(debug) << "command 'restart'";
			if(in_shell){
				killbot(working, t1, nat_hand);
				send(new_socket, "ok", 2, 0);
				exit(42);
			}else{
				send(new_socket, "not supported.", 14, 0);
			}
		}
	}

	return 0;
}
