# Telegram Bot
## Description
Library for those who want to create telegram bot on c++, but don't want to write a lot of code and search bugs. 
Based on: https://github.com/reo7sp/tgbot-cpp
## Installation
 - Install Boost, OpenSSL, PostreSQL, CURL
 
   ```sudo apt-get install g++ make binutils cmake libssl-dev libboost-all-dev zlib1g-dev libcurl4-openssl-dev```
 - After that you must install program
   ```
   git clone https://github.com/iamandrii/telegram-bot
   cmake .
   make
   ```
 - And update config (see https://github.com/iamandrii/telegram-bot#config)
 - And finally start bot by `./bot`
   
   
## Config
 `token` - bot token (get it at https://t.me/botfather)
 
 `dev_token` - token for starting bot with `--dev` argument.
 
 `triggered_sticker`, `news_channel`, `news_last_message`, `fame_chat_id`, `fame_chat_link` - need for modules in `App::Callback`
 
 `loglevel` - logging level. Maybe: debug, info, warning, error, fatal.
 
 `PG_string_auth` - authentication string for `App::Database` module (using postgres)
 
 you can also set config on starting bot in format
 ```
 ./bot --config:parameter=value
 ```
