#pragma once

#include <tgbot/tgbot.h>
#include <regex>
#include "../AppEvent/Event.h"
#include "../AppExceptions/Exceptions.h"

typedef function<void(TgBot::Bot, App::Event*)> callback_type;

namespace App{
    namespace HandlersEngine{
        class Matcher{
        private:
            bool is_text = true;
            regex text_condition;
            bool text_case_insective = true;
        public:
            const char* matcher_code = "";
            Matcher();
            Matcher(const char* code, regex rgx, bool case_insective = true);

            bool matches(App::Event* event);
            bool matches(TgBot::Message::Ptr message);
        };

        class AbstractCallback{
        public:
            AbstractCallback();
            pair<Matcher, callback_type> handler{Matcher(), [](TgBot::Bot bot, App::Event* event){
                throw App::Exceptions::NotImplementedError();
            }};
        };

        class Handler{
        private:
            vector<pair<Matcher, callback_type>>* registered = new vector<pair<Matcher, callback_type>>();
        public:
            void register_callback(Matcher matcher, callback_type call) = delete;

            void register_callback(const pair<Matcher, callback_type>& pr);

            template<typename T>
            void register_callback();

            void handle(TgBot::Bot bot, App::Event* event);
        };
    }
}