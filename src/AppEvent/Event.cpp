#include "Event.h"
#include "../AppConfig/Config.h"

using namespace App;

Event::Event(TgBot::Message::Ptr message, Database::Database* db, Config* config) :
    message(message),
    db(db),
    config(config) {};

Event::Event(TgBot::Message::Ptr message, App::Database::Database* db, App::Config* config, App::User* user, App::Group* group) :
    message(message),
    db(db),
    config(config),
    user(user),
    group(group) {};

TgBot::Message::Ptr Event::getMessage(){
    return this->message;
}

App::Database::Database* Event::getDatabase(){
    return this->db;
}

App::Config* Event::getConfig(){
    return this->config;
}

App::User* Event::getUser(){
    return this->user;
}

App::Group* Event::getGroup(){
    return this->group;
}