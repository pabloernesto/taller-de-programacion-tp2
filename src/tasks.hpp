#include "SourceSink.hpp"
#include <regex>

#ifndef TASKS_H
#define TASKS_H

class Echo {
    Source &input;
    Sink &output;

public:
    Echo(Source &input, Sink &output);
    void operator()();
};

class Match {
    std::basic_regex<char> r;
    Source &input;
    Sink &output;

public:
    Match(std::string regex, Source &input, Sink &output);
    void operator()();
};

#endif

