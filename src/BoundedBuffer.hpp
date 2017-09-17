#include <list>
#include <mutex>
#include <condition_variable>

#ifndef BOUNDED_BUFFER_H
#define BOUNDED_BUFFER_H

/* This buffer is first-in-first-out (FIFO), i.e. the elements will pop out
 * from it in the order they were pushed in. */
template<typename T>
class BoundedBuffer {
    int maxsize;
    std::list<T> buffer;
    std::mutex m;
    std::condition_variable full;
    std::condition_variable empty;

public:
    BoundedBuffer();
    BoundedBuffer(int maxsize);

    void push(T x);
    T pop();
    bool isEmpty();
    bool isFull();
};

#endif
