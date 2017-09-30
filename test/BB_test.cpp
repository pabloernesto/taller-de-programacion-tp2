#include "BoundedBuffer.hpp"
#include "tasks.hpp"
#include "iowrappers.hpp"
#include <iostream>
#include <thread>

using namespace std;

int main(int argc, char **argv) {
    StdinWrapper in;
    StdoutWrapper out;
    BoundedBuffer b;

    Echo e1(&in, &b);
    Echo e2(&b, &out);

    thread t1{e1};
    thread t2{e2};

    t1.join();
    t2.join();
}
