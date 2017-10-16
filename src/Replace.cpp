#include "tasks.h"
#include "SourceSink.h"
#include "Logger.h"

#include <string>
#include <regex>

using namespace std;

Replace::Replace(string regex, string &&rep, Source *input, Sink *output)
        : Replace(regex, move(rep), input, output, nullptr) {}

Replace::Replace(string regex, string &&rep, Source *input, Sink *output,
        Log *log)
        : r(regex), replacement(std::move(rep)), input(input),
          output(output), log(log) {}

void Replace::operator()() {
    while (!input->isAtEnd()) {
        string s = input->pop();
        string t = regex_replace(s, this->r, this->replacement);
        if (log) log->push(s + " -> " + t);
        output->push(t);
    }
    output->close();
    if (log) log->close();
}
