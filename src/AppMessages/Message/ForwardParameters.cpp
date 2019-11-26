#include "../Messages.h"

#include <bits/stdc++.h>
#include <tgbot/tgbot.h>
#include "../../AppEvent/Event.h"

using namespace std;

using namespace App;


Message::ForwardParameters::ForwardParameters(TgBot::Message::Ptr mess) :
    chat_id(mess->chat->id),
    message_id(mess->messageId) {};

Message::ForwardParameters::ForwardParameters(App::Event* event) : ForwardParameters(event->getMessage()) {};

Message::ForwardParameters::ForwardParameters(){};

Message::ForwardParameters::ForwardParameters(long long chat_id, long long message_id) :
        chat_id(chat_id),
        message_id(message_id) {};

Message::ForwardParameters Message::ForwardParameters::setChatId(long long nw) {this->chat_id = nw; return *this;}
Message::ForwardParameters Message::ForwardParameters::setMessageId(long long nw) {this->message_id = nw; return *this;}

string Message::ForwardParameters::dump(){
	stringstream ss;
	ss << "chat_id: " << this->chat_id << "; message_id: " << this->message_id;
	return ss.str();
}

