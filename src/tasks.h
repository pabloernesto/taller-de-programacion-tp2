#include "SourceSink.h"
#include <regex>

#ifndef TASKS_H
#define TASKS_H

class Task {
public:
    virtual ~Task();
    virtual void operator()();
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

class Replace : public Task {
    std::basic_regex<char> r;
    std::string replacement;
    Source *input;
    Sink *output;

public:
    Replace(std::string regex, std::string rep, Source *input, Sink *output);
    ~Replace();
    void operator()();
};

#endif

