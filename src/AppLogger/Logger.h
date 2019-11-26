#pragma once

#include <bits/stdc++.h>
using namespace std;

namespace App{
    static enum LogLevel{
        DEBUG,
        INFO,
        WARNING,
        ERROR,
        FATAL
    };

    class Logger{
    private:
        FILE* out;
        LogLevel level;
    public:
        Logger(FILE* out) :
            out(out),
            level(WARNING);
        Logger(FILE* out, LogLevel level) :
            out(out),
            level(level);

        void log(LogLevel level, const char* tag, const char* message);
    };
}
