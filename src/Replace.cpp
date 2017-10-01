#include "tasks.hpp"
#include "SourceSink.hpp"

#include <string>
#include <regex>

using namespace std;

Replace::Replace(string regex, string rep, Source *input, Sink *output)
        : r(regex), replacement(rep), input(input), output(output) {}

Replace::~Replace() {}

void Replace::operator()() {
    while (!input->isAtEnd()) {
        string s = input->pop();
        output->push(regex_replace(s, this->r, this->replacement));
    }
    output->close();
}
