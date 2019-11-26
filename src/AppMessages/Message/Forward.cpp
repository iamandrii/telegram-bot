#include "../Messages.h"
#include <boost/log/trivial.hpp>

#include <tgbot/tgbot.h>
#include "../../AppExceptions/Exceptions.h"

using namespace std;

using namespace App;

Message::Forward::Forward(App::Message::Parameters send, App::Message::ForwardParameters params_) :
	sendparams(send),
	fromparams(params_) {};

void Message::Forward::send(TgBot::Bot bot){
	if(this->sendparams.to_chat == -1 || this->fromparams.chat_id == -1 || this->fromparams.message_id == -1) throw App::Exceptions::UndefinedVariableError("Not all parameters is defined");
	bot.getApi().forwardMessage(this->sendparams.to_chat, this->fromparams.chat_id, this->fromparams.message_id, this->sendparams.silent);
	BOOST_LOG_TRIVIAL(debug) << "forward message";
	BOOST_LOG_TRIVIAL(debug) << '\t' << "sendparams " << this->sendparams.dump();
	BOOST_LOG_TRIVIAL(debug) << '\t' << "fromparams " << this->fromparams.dump();
}