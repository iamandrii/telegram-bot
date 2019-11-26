#include "../Exceptions.h"

using namespace App::Exceptions;

UndefinedVariableError::UndefinedVariableError(const char* message){
    this->msg = (char*)message;
};