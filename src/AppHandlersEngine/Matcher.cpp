#include "HandlersEngine.h"

#include <tgbot/tgbot.h>
#include <regex>
#include "../AppEvent/Event.h"

using namespace App::HandlersEngine;

Matcher::Matcher(){};
Matcher::Matcher(const char* code, regex rgx, bool case_insective) :
    matcher_code(code),
    text_condition(rgx),
    text_case_insective(case_insective) {};

bool Matcher::matches(App::Event* event){
    return this->matches(event->getMessage());
}

bool Matcher::matches(TgBot::Message::Ptr message){
    bool res = true;
    string to_check = message->text;
    if(this->text_case_insective){
        transform(to_check.begin(), to_check.end(), to_check.begin(),
                  [](unsigned char c){ return std::tolower(c); });
    }
    if(is_text) res = res & regex_match(to_check, text_condition);
    else res = false;
    return res;
}