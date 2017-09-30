#include "tasks.hpp"
#include <string>

using namespace std;


Echo::Echo(Source *input, Sink *output) : input(input), output(output) {}

void Echo::operator()() {
    while (!input->isAtEnd())
        output->push(input->pop());
    output->close();
}

void Echo::setInput(Source *input) {
    this->input = input;
}

void Echo::setOutput(Sink *output) {
    this->output = output;
}
