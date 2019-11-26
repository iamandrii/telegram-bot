#include "Database.h"

#include "libpq-fe.h"

using namespace App::Database;

char* Escape::Identifier(App::Database::Database* conn, string original){
    return PQescapeIdentifier((conn->conn), original.c_str(), sizeof(original));
}

char* Escape::Literal(App::Database::Database* conn, string original){
    return PQescapeLiteral((conn->conn), original.c_str(), sizeof(original));
}

