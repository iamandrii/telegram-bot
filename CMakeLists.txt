cmake_minimum_required(VERSION 3.8)
project(bot)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -O3")
set(Boost_USE_MULTITHREADED ON)

find_package(Threads REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(Boost COMPONENTS system log REQUIRED)
find_package(PostgreSQL REQUIRED)
find_package(CURL REQUIRED)
include_directories(/usr/local/include ${OPENSSL_INCLUDE_DIR} ${Boost_INCLUDE_DIR} ${PostgreSQL_INCLUDE_DIRS} ${CURL_INCLUDE_DIRS})

add_definitions(-DHAVE_CURL -DBOOST_LOG_DYN_LINK)

add_executable(bot
        src/AppConfig/Config.cpp

        src/AppEvent/Event.cpp

        src/AppHandlersEngine/AbstractCallback.cpp
            src/AppHandlersEngine/Matcher.cpp src/AppHandlersEngine/Handler.cpp

        src/AppMessages/AbstractMessage.cpp
            src/AppMessages/Message/Parameters.cpp src/AppMessages/Message/ForwardParameters.cpp
            src/AppMessages/Message/Text.cpp src/AppMessages/Message/Sticker.cpp src/AppMessages/Message/Forward.cpp

        src/AppDatabase/Result.cpp
            src/AppDatabase/Database.cpp src/AppDatabase/Escape.cpp

        src/AppUser/User.cpp src/AppGroup/Group.cpp

        src/AppExceptions/Exceptions/Exception.cpp
        src/AppExceptions/Exceptions/PostgresError.cpp src/AppExceptions/Exceptions/IdentifierError.cpp src/AppExceptions/Exceptions/UndefinedVariableError.cpp
        src/AppExceptions/Exceptions/DatabaseUnsetError.cpp src/AppExceptions/Exceptions/NotImplementedError.cpp

        src/AppBot/Bot.cpp

        src/main.cpp)
add_executable(sockcontrol src/sockcontrol.cpp)

target_link_libraries(bot /usr/local/lib/libTgBot.a ${CMAKE_THREAD_LIBS_INIT} ${OPENSSL_LIBRARIES} ${Boost_LIBRARIES} ${CURL_LIBRARIES} ${PostgreSQL_LIBRARIES})
