#include "../Exceptions.h"

using namespace App;

Exception::Exception(){};
Exception::Exception(char* msg) :
        msg(msg) {};
const char* Exception::what() const throw() {
    char* out = new char;
    sprintf(out, "ERROR, THROW %s WITH [%s]", this->className, this->msg);
    return out;
}