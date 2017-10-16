/* This classes wrap standard input and output facilities with Source and Sink
 * interfaces. */

#include "SourceSink.h"
#include <string>

#ifndef IOWRAP_H
#define IOWRAP_H

class StdinWrapper : public Source {
public:
    std::string pop();
    bool isAtEnd();
};

class StdoutWrapper : public Sink {
public:
    void push(const std::string &x);
    void close();
};

#endif

