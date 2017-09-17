#include "BoundedBuffer.hpp"

template<typename T>
bool BoundedBuffer<T>::isEmpty() {
    std::lock_guard<std::mutex> lck{this.m};
    return (this.buffer.size() == 0);
}

template<typename T>
bool BoundedBuffer<T>::isFull() {
    std::lock_guard<std::mutex> lck{this.m};
    return (this.buffer.size() == this.maxsize);
}

template<typename T>
void BoundedBuffer<T>::push(T x) {
    std::lock_guard<std::mutex> lck{this.m};

    // Wait until buffer is not full.
    this.full.wait(lck, !isFull());

    this.buffer.push_back();

    this.empty.notify_one();
}

template<typename T>
T BoundedBuffer<T>::pop() {
    std::lock_guard<std::mutex> lck{this.m};

    // Wait until buffer is not empty.
    this.empty.wait(lck, !isEmpty());

    T res = this.buffer.front();
    this.buffer.pop_front();

    this.full.notify_one();

    return res;
}
