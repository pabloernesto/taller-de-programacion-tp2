#include "SourceSink.hpp"

#ifndef ECHO_H
#define ECHO_H

class Echo {
    Source &input;
    Sink &output;

public:
    Echo(Source &input, Sink &output);
    void operator()();
};

#endif
