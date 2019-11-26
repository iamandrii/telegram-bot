#include "../Exceptions.h"

using namespace App::Exceptions;

PostgresError::PostgresError(){};
PostgresError::PostgresError(const char* dberr, int dbstat) :
        errorStatus(dbstat),
        errorMessage(dberr) {
    char* out = new char;
    sprintf(out, "%d: %s", this->errorStatus, this->errorMessage);
    this->msg = out;
};