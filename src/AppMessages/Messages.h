#pragma once

#include <bits/stdc++.h>
#include <tgbot/tgbot.h>
#include "../AppEvent/Event.h"

using namespace std;
namespace App{

	class AbstractMessage{
	public:
		void send(TgBot::Bot bot);
	};

	namespace Message{

		class Parameters{
		public:
			long long to_chat = -1, reply_to = 0;
			bool disable_web_page_preview = false;
			string parse_mode = "";
			bool silent = false;

			Parameters(App::Event* event, bool as_reply = false);
			Parameters(TgBot::Message::Ptr message, bool as_reply = false);
			Parameters();
			Parameters(long long to_chat_, long long reply_to_ = 0, bool disable_web_page_preview_ = false, string parse_mode_ = "", bool silent_ = false);

			Parameters setToChat(long long new_to_chat);
			Parameters setDisableWebPagePreview(bool nw);
			Parameters setParseMode(string nw);
			Parameters setReplyTo(long long nw);
			Parameters setSilent(bool nw);

			string dump();
		};


		class ForwardParameters{
		public:
			long long chat_id = -1, message_id = -1;

			ForwardParameters(TgBot::Message::Ptr mess);
			ForwardParameters(App::Event* event);
			ForwardParameters();
			ForwardParameters(long long chat_id, long long message_id);

			ForwardParameters setChatId(long long nw);
			ForwardParameters setMessageId(long long nw);

			string dump();
		};


		class Text : public App::AbstractMessage{
		private:
			string text;
			App::Message::Parameters params;

		public:
			Text(string text, App::Message::Parameters params);
			void send(TgBot::Bot bot);
		};


		class Sticker : public App::AbstractMessage{
		private:
			string sticker_id;
			App::Message::Parameters params;

		public:
			Sticker(string id, App::Message::Parameters params_);
			void send(TgBot::Bot bot);
		};


		class Forward : public App::AbstractMessage{
		private:
			App::Message::Parameters sendparams;
			App::Message::ForwardParameters fromparams;

		public:
			Forward(App::Message::Parameters send, App::Message::ForwardParameters params_);
			void send(TgBot::Bot bot);
		};
	}
}