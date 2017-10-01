#include "tasks.hpp"
#include "Logger.hpp"
#include <string>

using namespace std;

Echo::Echo(Source *input, Sink *output) {
    this->input = input;
    this->output = output;
}

Echo::~Echo() {}

void Echo::operator()() {
    Sink *log = Logger::requestLog("echo");
    while (true) {
        string s = input->pop();
        if (input->isAtEnd()) break;
        log->push(s + " -> " + s);
        output->push(s);
    }
    output->close();
    log->close();
}
