#include "tasks.h"
#include "iowrappers.h"
#include <thread>

using namespace std;

int main(int argc, char **argv) {
    StdinWrapper in;
    StdoutWrapper out;

    Replace m("regex", "rep", &in, &out);

    thread t{m};
    t.join();
}

