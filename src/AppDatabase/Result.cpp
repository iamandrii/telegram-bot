#include "Database.h"

#include "libpq-fe.h"

using namespace App::Database;

Result::Result(PGresult* mres){
    this->res = mres;
}

Result* Result::at(int id){
    this->current_row = id;
    return this;
}

template<typename T>
T* Result::get_bin(int column){
    return reinterpret_cast<T*>(PQgetvalue(this->res, this->current_row, column));
}

long long* Result::get_num(int column){
    char* x = PQgetvalue(this->res, this->current_row, column);
    void* xp = static_cast<void*>(x);
    long long pos = 0;
    long long num = 0;
    while(*(static_cast<char*>(xp)+pos) != '\0'){
        num*=10;
        num+=(*(static_cast<char*>(xp)+pos) - '0');
        pos++;
    }
    auto pt = new long long(num);
    return pt;
}

char* Result::get_text(int column){
    return PQgetvalue(this->res, this->current_row, column);
}

template<typename T>
T* Result::get(int row, int column){
    this->current_row = row;
    return this->get<T>(column);
}

long long Result::affected(){
    return PQntuples(this->res);
}