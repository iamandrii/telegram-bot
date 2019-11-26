#include "Messages.h"
#include "../AppExceptions/Exceptions.h"
#include <tgbot/tgbot.h>

using namespace App;

void AbstractMessage::send(TgBot::Bot bot) {
    throw Exceptions::NotImplementedError();
}