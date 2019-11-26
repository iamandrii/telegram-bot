#pragma once

#include <bits/stdc++.h>

#include "libpq-fe.h"
#include "../AppConfig/Config.h"

using namespace std;

namespace App{
    namespace Database{
        class Result{
        private:
            int current_row = 0;
        public:
            PGresult* res;

            Result(PGresult* mres);

            Result* at(int id);

            template<typename T>
            T* get_bin(int column);

            long long* get_num(int column);

            char* get_text(int column);

            template<typename T>
            T* get(int row, int column);

            long long affected();
        };

        class Database{
        private:
            PGresult* res = nullptr;
        public:
            PGconn* conn = nullptr;
            bool unset;

            Database(bool unset);

            Database(App::Config* config);

            Result* select(string rq);

            Result* insert(string rq);

            void update_index(const char* table, const char* column, const char* seq);

            void clearRes();

            void terminate();

            void terminate_error(bool on_connection = false);
        };

        namespace Escape{
            char* Identifier(App::Database::Database* conn, string original);

            char* Literal(App::Database::Database* conn, string original);
        }
    }
}