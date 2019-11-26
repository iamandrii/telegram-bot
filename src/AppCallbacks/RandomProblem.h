#pragma once

#include <bits/stdc++.h>
#include <tgbot/tgbot.h>
#include <curl/curl.h>
#include <boost/log/trivial.hpp>
#include "../AppMessages/Messages.h"
#include "../AppHandlersEngine/HandlersEngine.h"
#include "../AppEvent/Event.h"
#include "../libs/json.hpp"
using json = nlohmann::json;
using namespace std;
namespace App{
	namespace Callbacks{
		class RandomProblem : public App::HandlersEngine::AbstractCallback{
		private:
			static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp){
				((std::string*)userp)->append((char*)contents, size * nmemb);
				return size * nmemb;
			}
			const char* code = "randomproblem";
		public:
			RandomProblem(){};
			pair<App::HandlersEngine::Matcher, function<void(TgBot::Bot, App::Event *)>> operator()() {
				return {
					App::HandlersEngine::Matcher(this->code, regex("/randomproblem(@.*)?")),
					[](TgBot::Bot bot, App::Event *event) {
						BOOST_LOG_TRIVIAL(debug) << "RandomProblem parsing...";
						stringstream ss;
						ss << event->getUser()->makeMention();
						ss << ", ТИ ПОВИНЕН ВИРІШИТИ ";

						CURL *curl;
						//CURLcode res;
						string readBuffer;
						curl = curl_easy_init();
						if (curl) {
							curl_easy_setopt(curl, CURLOPT_URL, "http://codeforces.com/api/problemset.problems");
							curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
							curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
							curl_easy_perform(curl);
							curl_easy_cleanup(curl);
							json problems;
							problems = json::parse(readBuffer.c_str());
							if (problems["status"] != "OK") {
								App::Message::Text("Got <b>error</b> response from codeforces",
												   App::Message::Parameters(event, true).setParseMode("HTML")).send(
										bot);
							}
							int at = rand() % (problems["result"]["problems"].size());
							int contest = problems["result"]["problems"][at]["contestId"].get<int>();
							string index = problems["result"]["problems"][at]["index"].get<string>();
							ss << "<a href=\"";
							ss << "https://codeforces.com/problemset/problem/";
							ss << contest;
							ss << "/";
							ss << index;
							ss << "\">";
							ss << contest;
							ss << index;
							ss << "</a>";
							App::Message::Text(ss.str(),
											   App::Message::Parameters(event, true).setParseMode("HTML")).send(
									bot);
						} else {
							App::Message::Text("Got error with <b>CURL</b>",
											   App::Message::Parameters(event, true).setParseMode("HTML")).send(
									bot);
						}
					}
				};
			}
		};
	}
}