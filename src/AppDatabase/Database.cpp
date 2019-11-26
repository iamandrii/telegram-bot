#include "Database.h"
#include <boost/log/trivial.hpp>

#include "libpq-fe.h"
#include "../AppConfig/Config.h"
#include "../AppExceptions/Exceptions.h"

using namespace App::Database;

Database::Database(bool unset) :
    unset(true) {
    this->conn = nullptr;
    BOOST_LOG_TRIVIAL(trace) << "database object created like empty";
};

Database::Database(App::Config* config) :
    unset(false) {
    this->conn = PQconnectdb(config->get<string>("PG_string_auth").c_str());
    if(PQstatus(this->conn) != CONNECTION_OK) this->terminate_error(true);
    BOOST_LOG_TRIVIAL(info) << "database object created";
}

Result* Database::select(const string rq){
    BOOST_LOG_TRIVIAL(trace) << "database query: " << rq;
    this->clearRes();
    this->res = PQexec(this->conn, rq.c_str());
    if(PQresultStatus(this->res) != PGRES_TUPLES_OK) terminate_error();
    auto* xr = new App::Database::Result(this->res);
    return xr;
}

Result* Database::insert(const string rq){
    BOOST_LOG_TRIVIAL(trace) << "database query: " << rq;
    this->res = PQexec(conn, rq.c_str());
    if(PQresultStatus(res) != PGRES_COMMAND_OK) terminate_error();
    auto* xr = new App::Database::Result(this->res);
    this->clearRes();
    return xr;
}

void Database::update_index(const char* table, const char* column, const char* seq){
    this->clearRes();
    stringstream ss;
    ss << "SELECT setval('";
    ss << seq;
    ss << "', MAX(";
    ss << App::Database::Escape::Identifier(this, string(column));
    ss << "), true) FROM ";
    ss << App::Database::Escape::Identifier(this, string(table));
    ss << ";";

    BOOST_LOG_TRIVIAL(trace) << "database query: " << ss.str();
    this->res = PQexec(conn, ss.str().c_str());
    if(PQresultStatus(res) != PGRES_TUPLES_OK) terminate_error();
}

void Database::clearRes(){
    PQclear(this->res);
    this->res = nullptr;
}

void Database::terminate(){
    BOOST_LOG_TRIVIAL(debug) << "database terminated";
    if(this->res != nullptr) this->clearRes();
    if(this->conn != nullptr) PQfinish(this->conn);
}

void Database::terminate_error(bool on_connection){
    BOOST_LOG_TRIVIAL(info) << "database error";
    if(!on_connection){
        throw App::Exceptions::PostgresError(PQresultErrorMessage(this->res), PQresultStatus(this->res));
    }else{
        throw App::Exceptions::PostgresError(PQerrorMessage(this->conn), PQstatus(this->conn));
    }
}