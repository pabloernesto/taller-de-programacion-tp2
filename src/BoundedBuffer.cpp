#include "BoundedBuffer.hpp"

using namespace std;

BoundedBuffer::BoundedBuffer() : maxsize(10), closed(false) {}

BoundedBuffer::BoundedBuffer(unsigned int maxsize) : maxsize(maxsize),
        closed(false) {}

bool BoundedBuffer::isEmpty() {
    return (this->buffer.size() == 0);
}

bool BoundedBuffer::isFull() {
    return (this->buffer.size() == this->maxsize);
}

bool BoundedBuffer::isAtEnd() {
    unique_lock<mutex> lck{this->m};
    return (this->isEmpty() && this->closed);
}

void BoundedBuffer::push(string x) {
    unique_lock<mutex> lck{this->m};

    if (this->closed) throw;

    // Wait until buffer is not full.
    if (this->isFull())
        this->full.wait(lck, [this]{return !this->isFull();});

    this->buffer.push_back(x);
    this->empty.notify_one();
}

string BoundedBuffer::pop() {
    unique_lock<mutex> lck{this->m};

    // Wait until buffer is not empty or is closed.
    if (this->isEmpty())
        this->empty.wait(lck, [this]{return this->closed || !this->isEmpty();});

    if (this->isEmpty()) throw;

    string res = this->buffer.front();
    this->buffer.pop_front();

    this->full.notify_one();
    return res;
}

void BoundedBuffer::close() {
    unique_lock<mutex> lck{this->m};
    this->closed = true;
    this->empty.notify_all();
}
