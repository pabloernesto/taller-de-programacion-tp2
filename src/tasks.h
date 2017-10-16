#include "SourceSink.h"
#include "Logger.h"
#include <regex>

#ifndef TASKS_H
#define TASKS_H

class Echo {
    Source *input;
    Sink *output;
    Log *log;

    public:
    Echo(Source *input, Sink *output);
    Echo(Source *input, Sink *output, Log *log);
    void operator()();
};

class Match {
    std::basic_regex<char> r;
    Source *input;
    Sink *output;
    Log *log;

    public:
    Match(std::string regex, Source *input, Sink *output);
    Match(std::string regex, Source *input, Sink *output, Log *log);
    void operator()();
};

class Replace {
    std::basic_regex<char> r;
    std::string replacement;
    Source *input;
    Sink *output;
    Log *log;

    public:
    Replace(std::string regex, std::string &&rep, Source *input, Sink *output);
    Replace(std::string regex, std::string &&rep, Source *input, Sink *output,
            Log *log);
    void operator()();
};

#endif

