#include "../Exceptions.h"

using namespace App::Exceptions;

IdentifierError::IdentifierError(){};
IdentifierError::IdentifierError(const char* modifier, const char* msg){
    sprintf(this->msg, "%s: %s", modifier, msg);
};