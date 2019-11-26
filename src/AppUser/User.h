#pragma once

#include <bits/stdc++.h>
#include "../AppDatabase/Database.h"

using namespace std;

namespace App{
    class User{
    private:
        bool synced_up = false;
        template<typename T>
        void sync_down_low_level(string column_name, T column_value);
        void sync_down();
    public:
        long long row_id, tg_id;
        string first_name, username;
        App::Database::Database* db = new App::Database::Database(true);

        User();
        User(long long row_id, bool by_row_id);
        User(long long tg_id);
        User(string username);
        User(User &a);
        User(long long tg_id, string first_name, string username);

        void sync_up();

        User* setDB(App::Database::Database* db);

        string getName();
        string getUsername();
        long long getTgId();
        long long getRowId();

        void re_sync_down();

        string makeMention();

        string dump();
    };
}