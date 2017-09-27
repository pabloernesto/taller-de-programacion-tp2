#include <list>
#include <mutex>
#include <string>
#include <condition_variable>
#include "SourceSink.hpp"

#ifndef BOUNDED_BUFFER_H
#define BOUNDED_BUFFER_H

/* This buffer is first-in-first-out (FIFO), i.e. the elements will pop out
 * from it in the order they were pushed in. */
class BoundedBuffer : public Source, public Sink {
    const unsigned int maxsize;
    bool closed;
    std::list<std::string> buffer;
    std::mutex m;
    std::condition_variable full;
    std::condition_variable empty;

public:
    BoundedBuffer();
    BoundedBuffer(unsigned int maxsize);

    void push(std::string x);
    void close();

    std::string pop();
    bool isAtEnd();

private:
    bool isEmpty();
    bool isFull();
};

#endif
