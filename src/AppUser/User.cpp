#include "User.h"
#include "../AppExceptions/Exceptions.h"
#include <boost/log/trivial.hpp>

using namespace std;
using namespace App;

template <typename T>
void User::sync_down_low_level(string column_name, T column_value){
    stringstream ss, ss2;
    ss2 << column_value;
    ss << "SELECT * FROM ";
    ss << App::Database::Escape::Identifier(this->db, "users");
    ss << " WHERE ";
    ss << App::Database::Escape::Identifier(this->db, column_name);
    ss << " = ";
    ss << App::Database::Escape::Literal(this->db, ss2.str());
    ss << ";";
    App::Database::Result* res = this->db->select(ss.str());
    if(res->affected() == 0) throw App::Exceptions::IdentifierError("USER", "undefined data");
    else if(res->affected() > 1) throw App::Exceptions::IdentifierError("USER", "more > 1 rows");
    else{
        this->row_id = *(res->at(0)->get_num(0));
        this->tg_id = *(res->at(0)->get_num(1));
        this->first_name = string((res->at(0)->get_text(2)));
        this->username = string((res->at(0)->get_text(3)));
        BOOST_LOG_TRIVIAL(trace) << "user synced down";
    }
}

void User::sync_down(){
    if(this->db->unset) throw App::Exceptions::DatabaseUnsetError();
    if(this->row_id != 0) this->sync_down_low_level("row_id", this->row_id);
    else if(this->tg_id != 0) this->sync_down_low_level("tg_id", this->tg_id);
    else if(!this->username.empty()) this->sync_down_low_level("username", this->username);
    else throw App::Exceptions::IdentifierError("USER", "Object is unset");
}

User::User(){};
User::User(long long row_id, bool by_row_id) :
        row_id(row_id),
        tg_id(0),
        first_name(""),
        username("") {};
User::User(long long tg_id) :
        row_id(0),
        tg_id(tg_id),
        first_name(""),
        username("") {};
User::User(string username) :
    row_id(0),
    tg_id(0),
    first_name(""),
    username(username) {};
User::User(User &a) :
    row_id(a.row_id),
    tg_id(a.tg_id),
    first_name(a.first_name),
    username(a.username) {};
User::User(long long tg_id, string first_name, string username) :
        row_id(0),
        tg_id(tg_id),
        first_name(first_name),
        username(username) {};

void User::sync_up(){
    if(this->db->unset) throw App::Exceptions::DatabaseUnsetError();
    if(this->tg_id != 0 && this->first_name != ""){
        stringstream ss;
        ss << "INSERT INTO users(tg_id, first_name, username) VALUES(";
        ss << this->tg_id;
        ss << ", ";
        ss << App::Database::Escape::Literal(this->db, this->first_name);
        ss << ", ";
        ss << App::Database::Escape::Literal(this->db, this->username);
        ss << ") ON CONFLICT ON CONSTRAINT user_unique DO UPDATE SET ";
        ss << App::Database::Escape::Identifier(this->db, "first_name");
        ss << " = ";
        ss << "EXCLUDED.first_name";
        ss << ", ";
        ss << App::Database::Escape::Identifier(this->db, "username");
        ss << " = ";
        ss << "EXCLUDED.username";
        ss << ";";

        const auto res = this->db->insert(ss.str());
        delete res;

        this->db->update_index("users", "row_id", "users_row_id_seq");
        BOOST_LOG_TRIVIAL(trace) << "user synced up";
    }else{
        throw App::Exceptions::IdentifierError("USER", "Object is unset");
    }
}

User* User::setDB(App::Database::Database* db){
    this->db = db;
    return this;
}


string User::getName(){
    if(this->first_name == "") this->sync_down();
    return this->first_name;
}

string User::getUsername(){
    if(this->username == "") this->sync_down();
    return this->username;
}

long long User::getTgId(){
    if(this->tg_id == 0) this->sync_down();
    return this->tg_id;
}

long long User::getRowId(){
    if(this->row_id == 0) this->sync_down();
    return this->row_id;
}

void User::re_sync_down(){
    this->sync_down();
}

string User::makeMention(){
    if(this->getUsername().empty()){
        string name = this->getName();
        stringstream ss;
        ss << "<a href=\"tg://user?id=";
        ss << this->getTgId();
        ss << "\">";
        ss << name;
        ss << "</a>";
        return ss.str();
    }else{
        return "@"+this->getUsername();
    }
}

string User::dump(){
    stringstream ss;
    ss << "row_id: ";ss << this->row_id;ss << " ";
    ss << "tg_id: ";ss << this->tg_id;ss << " ";
    ss << "first_name: ";ss << this->first_name;ss << " ";
    ss << "username: ";ss << this->username;ss << " ";
    return ss.str();
}
