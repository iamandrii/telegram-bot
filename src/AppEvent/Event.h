#pragma once

#include <tgbot/tgbot.h>
#include "../AppDatabase/Database.h"
#include "../AppConfig/Config.h"
#include "../AppUser/User.h"
#include "../AppGroup/Group.h"

namespace App{
    class Event{
    private:
        TgBot::Message::Ptr message;
        App::Database::Database* db;
        App::Config* config;
        App::User* user = nullptr;
        App::Group* group = nullptr;
    public:
        Event(TgBot::Message::Ptr message, App::Database::Database* db, App::Config* config);

        Event(TgBot::Message::Ptr message, App::Database::Database* db, App::Config* config, App::User* user, App::Group* group);

        TgBot::Message::Ptr getMessage();

        App::Database::Database* getDatabase();

        App::User* getUser();

        App::Group* getGroup();

        App::Config* getConfig();
    };
}