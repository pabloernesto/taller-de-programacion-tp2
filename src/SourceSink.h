#include <string>

#ifndef SOURCE_SINK_H
#define SOURCE_SINK_H

class Source {
public:
    virtual ~Source() {};
    virtual std::string pop() = 0;
    virtual bool isAtEnd() = 0;
};

class Sink {
public:
    virtual ~Sink() {};
    virtual void push(const std::string &x) = 0;
    virtual void close() = 0;
};

#endif
