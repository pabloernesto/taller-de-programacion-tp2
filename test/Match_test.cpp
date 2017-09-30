#include "tasks.hpp"
#include "iowrappers.hpp"
#include <thread>

using namespace std;

int main(int argc, char **argv) {
    StdinWrapper in;
    StdoutWrapper out;

    Match m("regex", &in, &out);

    thread t{m};
    t.join();
}
