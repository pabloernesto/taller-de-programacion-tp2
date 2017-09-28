#include "SourceSink.hpp"
#include <regex>

#ifndef MATCH_H
#define MATCH_H

class Match {
    std::basic_regex<char> r;
    Source &input;
    Sink &output;

public:
    Match(std::string regex, Source &input, Sink &output);
    void operator()();
};

#endif

