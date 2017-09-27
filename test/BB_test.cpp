#include "BoundedBuffer.hpp"
#include "Echo.hpp"
#include "iowrappers.hpp"
#include <iostream>
#include <thread>

using namespace std;

int main(int argc, char **argv) {
    StdinWrapper in;
    StdoutWrapper out;
    Echo e(in, out);

    thread t{e};
    t.join();
}
