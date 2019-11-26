#pragma once

#include <bits/stdc++.h>
#include "../AppDatabase/Database.h"
#include "../AppUser/User.h"

using namespace std;

namespace App{
    class Group{
    private:
        bool synced_up = false;
        vector<App::User*>* users = new vector<App::User*>();

        template<typename T>
        void sync_down_low_level(string column_name, T column_value);

        void sync_down_users_low_level();

        void sync_down();

        void sync_down_users();

    public:
        long long row_id = 0, tg_id = 0;
        string group_name;
        App::Database::Database* db = new App::Database::Database(true);

        Group();
        Group(long long row_id, bool by_row_id);
        Group(long long tg_id);
        Group(long long tg_id, string group_name);

        Group* setDB(App::Database::Database* db);

        Group* sync_up();

        string getName();
        long long getTgId();
        long long getRowId();
        vector<App::User*>* listUsers();

        void connectUser(User* user);

        string dump();
    };
}