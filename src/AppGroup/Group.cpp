#include <bits/stdc++.h>
#include <boost/log/trivial.hpp>
#include "Group.h"
#include "../AppDatabase/Database.h"
#include "../AppExceptions/Exceptions.h"
#include "../AppUser/User.h"
using namespace std;

using namespace App;

template<typename T>
void Group::sync_down_low_level(string column_name, T column_value){
    stringstream ss, ss2;
    ss2 << column_value;
    ss << "SELECT * FROM ";
    ss << App::Database::Escape::Identifier(this->db, "groups");
    ss << " WHERE ";
    ss << App::Database::Escape::Identifier(this->db, column_name);
    ss << " = ";
    ss << App::Database::Escape::Literal(this->db, ss2.str());
    auto res = this->db->select(ss.str());
    if(res->affected() == 0) throw App::Exceptions::IdentifierError("GROUP", "undefined data");
    else if(res->affected() > 1) throw App::Exceptions::IdentifierError("GROUP", "more > 1 rows");
    else{
        this->row_id = *(res->at(0)->get_num(0));
        this->tg_id = *(res->at(0)->get_num(1));
        this->group_name = string((res->at(0)->get_text(2)));
        BOOST_LOG_TRIVIAL(trace) << "synced down group";
    }
}

void Group::sync_down_users_low_level(){
    stringstream ss;
    ss << "SELECT users.* FROM groups_users_connect INNER JOIN users ON groups_users_connect.user_id = users.row_id where groups_users_connect.group_id = ";
    ss << this->row_id;
    ss << ";";
    users->clear();
    auto res = this->db->select(ss.str());
    for(int i = 0;i<res->affected();i++){
        auto* user = new App::User();
        user->row_id = *(res->at(i)->get_num(0));
        user->tg_id = *(res->at(i)->get_num(1));
        user->first_name = string((res->at(i)->get_text(2)));
        user->username = string((res->at(i)->get_text(3)));
        users->push_back(user);
    }
    BOOST_LOG_TRIVIAL(trace) << "synced down group members";
}

void Group::sync_down(){
    if(this->db->unset) throw App::Exceptions::DatabaseUnsetError();
    if(this->row_id != 0) this->sync_down_low_level("row_id", this->row_id);
    else if(this->tg_id != 0) this->sync_down_low_level("tg_id", this->tg_id);
    else throw App::Exceptions::IdentifierError("GROUP", "Object is unset");
}

void Group::sync_down_users(){
    if(this->db->unset) throw App::Exceptions::DatabaseUnsetError();
    if(this->row_id == 0) this->sync_down();
    this->sync_down_users_low_level();
}

Group::Group(){};
Group::Group(long long row_id, bool by_row_id) :
        row_id(row_id) {};
Group::Group(long long tg_id) :
        tg_id(tg_id) {};
Group::Group(long long tg_id, string group_name) :
        tg_id(tg_id),
        group_name(group_name) {};

Group* Group::setDB(App::Database::Database* db){
    this->db = db;
    return this;
}

Group* Group::sync_up(){
    if(this->db->unset) throw App::Exceptions::DatabaseUnsetError();
    if(this->tg_id != 0 && this->group_name != ""){
        stringstream ss;
        ss << "INSERT INTO groups(tg_id, group_name) VALUES(";
        ss << this->tg_id;
        ss << ", ";
        ss << App::Database::Escape::Literal(this->db, this->group_name);
        ss << ") ON CONFLICT ON CONSTRAINT group_unique DO UPDATE SET ";
        ss << App::Database::Escape::Identifier(this->db, "group_name");
        ss << " = ";
        ss << "EXCLUDED.group_name";
        ss << ";";

        const auto res = this->db->insert(ss.str());
        delete res;

        this->db->update_index("groups", "row_id", "groups_row_id_seq");
        BOOST_LOG_TRIVIAL(trace) << "synced up group";
    }else{
        throw App::Exceptions::IdentifierError("GROUP", "Object is unset");
    }
    return this;
}

string Group::getName(){
    if(this->group_name == "") this->sync_down();
    return this->group_name;
}

long long Group::getTgId(){
    if(this->tg_id == 0) this->sync_down();
    return this->tg_id;
}

long long Group::getRowId(){
    if(this->row_id == 0) this->sync_down();
    return this->row_id;
}

vector<App::User*>* Group::listUsers(){
    this->sync_down_users();
    return this->users;
}

void Group::connectUser(User* user){
    long long uid = user->getRowId();
    long long gid = this->getRowId();
    stringstream ss;
    ss << "INSERT INTO groups_users_connect(group_id, user_id) VALUES(";
    ss << gid;
    ss << ", ";
    ss << uid;
    ss << ") ON CONFLICT ON CONSTRAINT user_group_connect_unique DO NOTHING";
    ss << ";";
    const auto res = this->db->insert(ss.str());
    delete res;

    this->db->update_index("groups_users_connect", "row_id", "groups_users_connect_row_id_seq");
    BOOST_LOG_TRIVIAL(trace) << "connected user to group or did nothing";
}

string Group::dump(){
    stringstream ss;
    ss << "row_id: " << this->row_id << " ";
    ss << "tg_id: " << this->tg_id << " ";
    ss << "group_name: " << this->group_name;
    return ss.str();
}