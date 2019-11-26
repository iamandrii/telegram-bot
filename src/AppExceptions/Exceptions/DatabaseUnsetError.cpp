#include "../Exceptions.h"

using namespace App::Exceptions;

DatabaseUnsetError::DatabaseUnsetError() : UndefinedVariableError("Using unset database") {};