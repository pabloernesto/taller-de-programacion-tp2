#include "SourceSink.hpp"
#include <regex>

#ifndef TASKS_H
#define TASKS_H

class Task {
public:
    virtual ~Task();
    virtual void operator()() = 0;
};

class Echo : public Task {
    Source *input;
    Sink *output;

public:
    Echo(Source *input, Sink *output);
    ~Echo();
    void operator()();
};

class Match : public Task {
    std::basic_regex<char> r;
    Source *input;
    Sink *output;

public:
    Match(std::string regex, Source *input, Sink *output);
    ~Match();
    void operator()();
};

#endif

