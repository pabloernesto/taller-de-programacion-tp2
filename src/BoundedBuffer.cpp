#include "BoundedBuffer.hpp"

using namespace std;

BoundedBuffer::BoundedBuffer() : maxsize(10) {}

BoundedBuffer::BoundedBuffer(unsigned int maxsize) : maxsize(maxsize) {}

bool BoundedBuffer::isEmpty() {
    return (this->buffer.size() == 0);
}

bool BoundedBuffer::isFull() {
    return (this->buffer.size() == this->maxsize);
}

void BoundedBuffer::push(char* x) {
    unique_lock<mutex> lck{this->m};

    // Wait until buffer is not full.
    if (this->isFull())
        this->full.wait(lck, [this]{return !(this->isFull());});

    this->buffer.push_back(x);

    this->empty.notify_one();
}

char* BoundedBuffer::pop() {
    unique_lock<mutex> lck{this->m};

    // Wait until buffer is not empty.
    if (this->isEmpty())
        this->empty.wait(lck, [this]{return !(this->isEmpty());});

    char* res = this->buffer.front();
    this->buffer.pop_front();

    this->full.notify_one();

    return res;
}
