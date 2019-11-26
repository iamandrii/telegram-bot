#include "../Exceptions.h"

using namespace App::Exceptions;

NotImplementedError::NotImplementedError(){
    this->msg = (char*)"Not implemented";
}