#include "../Messages.h"

#include <bits/stdc++.h>
#include <tgbot/tgbot.h>
#include "../../AppEvent/Event.h"

using namespace std;

using namespace App;


Message::Parameters::Parameters(Event* event, bool as_reply) :
        to_chat(event->getMessage()->chat->id)
{if(as_reply) this->reply_to = event->getMessage()->messageId;};

Message::Parameters::Parameters(TgBot::Message::Ptr message, bool as_reply) :
        to_chat(message->chat->id)
{if(as_reply) this->reply_to = message->messageId;};

Message::Parameters::Parameters(){};

Message::Parameters::Parameters(long long to_chat_, long long reply_to_, bool disable_web_page_preview_, string parse_mode_, bool silent_) :
        to_chat(to_chat_),
        reply_to(reply_to_),
        disable_web_page_preview(disable_web_page_preview_),
        parse_mode(parse_mode_),
        silent(silent_) {}

Message::Parameters Message::Parameters::setToChat(long long new_to_chat) {this->to_chat = (new_to_chat); return *this;};
Message::Parameters Message::Parameters::setDisableWebPagePreview(bool nw) {this->disable_web_page_preview = (nw); return *this;};
Message::Parameters Message::Parameters::setParseMode(string nw) {this->parse_mode = (nw); return *this;};
Message::Parameters Message::Parameters::setReplyTo(long long nw) {this->reply_to = (nw); return *this;};
Message::Parameters Message::Parameters::setSilent(bool nw) {this->silent = (nw); return *this;};

string Message::Parameters::dump(){
	stringstream ss;
	ss << "to_chat " << this->to_chat << "; ";
	ss << "reply_to " << this->reply_to << "; ";
	ss << "disable_web_page_preview " << this->disable_web_page_preview << "; ";
	ss << "parse_mode " << this->parse_mode << "; ";
	ss << "silent " << this->silent;
	return ss.str();
}