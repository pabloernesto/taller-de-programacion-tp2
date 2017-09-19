#include "BoundedBuffer.hpp"
#include <iostream>
#include <thread>

using namespace std;

void read(BoundedBuffer &buf, int argc, char **argv) {
    for (int i = 1; i < argc; i++)
        buf.push(argv[i]);
}

void write(BoundedBuffer &buf, int argc) {
    for (int i = 1; i < argc; i++)
        cout << buf.pop() << endl;
}

int main(int argc, char **argv) {
    BoundedBuffer b(20);
    thread r{read, std::ref(b), argc, argv};
    thread w{write, std::ref(b), argc};

    r.join();
    w.join();
}
