#include "tasks.hpp"
#include <string>

using namespace std;

Echo::Echo(Source *input, Sink *output) {
    this->input = input;
    this->output = output;
}

Echo::~Echo() {}

void Echo::operator()() {
    while (!input->isAtEnd())
        output->push(input->pop());
    output->close();
}
