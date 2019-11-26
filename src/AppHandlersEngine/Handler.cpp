#include "HandlersEngine.h"
#include <boost/log/trivial.hpp>
#include <tgbot/tgbot.h>
#include "../AppEvent/Event.h"

using namespace App::HandlersEngine;

void Handler::register_callback(const pair<Matcher, callback_type> &pr){
    this->registered->emplace_back(pr);
    BOOST_LOG_TRIVIAL(debug) << "registered handler with code " << pr.first.matcher_code;
}

template<typename T>
void Handler::register_callback(){
    this->register_callback(T()());
}

void Handler::handle(TgBot::Bot bot, App::Event* event){
    for(unsigned long long i = 0;i<this->registered->size();i++){
        auto mt = (*(this->registered))[i];
        if(mt.first.matches(event)) {
            BOOST_LOG_TRIVIAL(info) << "found match for message at " << mt.first.matcher_code;
            mt.second(bot, event);
        }
    }
}