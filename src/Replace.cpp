#include "tasks.hpp"
#include "SourceSink.hpp"
#include "Logger.hpp"

#include <string>
#include <regex>

using namespace std;

Replace::Replace(string regex, string rep, Source *input, Sink *output)
        : r(regex), replacement(rep), input(input), output(output) {}

Replace::~Replace() {}

void Replace::operator()() {
    Sink *log = Logger::requestLog("replace");
    while (!input->isAtEnd()) {
        string s = input->pop();
        string t = regex_replace(s, this->r, this->replacement);
        log->push(s + " -> " + t);
        output->push(t);
    }
    output->close();
}
