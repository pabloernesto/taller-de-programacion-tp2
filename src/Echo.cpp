#include "tasks.h"
#include "Logger.h"
#include <string>

using namespace std;

Echo::Echo(Source *input, Sink *output) {
    this->input = input;
    this->output = output;
}

Echo::~Echo() {}

void Echo::operator()() {
    Sink *log = Logger::requestLog("echo");
    while (!input->isAtEnd()) {
        string s = input->pop();
        log->push(s + " -> " + s);
        output->push(s);
    }
    output->close();
    log->close();
}
