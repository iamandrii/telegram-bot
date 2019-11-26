#include "../Messages.h"

#include <boost/log/trivial.hpp>
#include <bits/stdc++.h>
#include <tgbot/tgbot.h>
#include "../../AppExceptions/Exceptions.h"

using namespace std;

using namespace App;

Message::Sticker::Sticker(string id, App::Message::Parameters params_) :
    sticker_id(id),
    params(params_) {};

void Message::Sticker::send(TgBot::Bot bot){
    if(this->params.to_chat == -1) throw App::Exceptions::UndefinedVariableError("Parameters.to_chat is undefined");
    bot.getApi().sendSticker(this->params.to_chat, this->sticker_id, this->params.reply_to, make_shared<TgBot::GenericReply>(), this->params.silent);
    BOOST_LOG_TRIVIAL(debug) << "sent sticker";
	BOOST_LOG_TRIVIAL(debug) << '\t' << "params " << this->params.dump();
	BOOST_LOG_TRIVIAL(debug) << '\t' << "sticker_id " << this->sticker_id;
}