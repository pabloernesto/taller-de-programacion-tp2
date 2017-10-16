#include "tasks.h"
#include "Logger.h"
#include <string>

using namespace std;

Echo::Echo(Source *input, Sink *output) : Echo(input, output, nullptr) {}

Echo::Echo(Source *input, Sink *output, Log *log)
        : input(input), output(output), log(log) {}

void Echo::operator()() {
    while (!input->isAtEnd()) {
        string s = input->pop();
        if (log) log->push(s + " -> " + s);
        output->push(s);
    }
    output->close();
    if (log) log->close();
}
