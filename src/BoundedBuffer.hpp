#include <list>
#include <mutex>
#include <condition_variable>

#ifndef BOUNDED_BUFFER_H
#define BOUNDED_BUFFER_H

/* This buffer is first-in-first-out (FIFO), i.e. the elements will pop out
 * from it in the order they were pushed in. */
class BoundedBuffer {
    const unsigned int maxsize;
    std::list<char*> buffer;
    std::mutex m;
    std::condition_variable full;
    std::condition_variable empty;

public:
    BoundedBuffer();
    BoundedBuffer(unsigned int maxsize);

    void push(char* x);
    char* pop();

private:
    bool isEmpty();
    bool isFull();
};

#endif
