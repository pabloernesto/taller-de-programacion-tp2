#include "BoundedBuffer.hpp"
#include <iostream>
#include <thread>

using namespace std;

void read(BoundedBuffer &buf, int argc, char **argv) {
    for (int i = 1; i < argc; i++)
        buf.push(argv[i]);
    buf.close();
}

void write(BoundedBuffer &buf) {
    char *s = buf.pop();
    while (s != nullptr) {
        cout << s << endl;
        s = buf.pop();
    }
}

int main(int argc, char **argv) {
    BoundedBuffer b(20);
    thread r{read, std::ref(b), argc, argv};
    thread w{write, std::ref(b)};

    r.join();
    w.join();
}
