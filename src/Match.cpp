#include "tasks.h"
#include "Logger.h"
#include <string>
#include <regex>

using namespace std;

Match::Match(std::string regex, Source *input, Sink *output)
        : Match(regex, input, output, nullptr) {}

Match::Match(std::string regex, Source *input, Sink *output, Log *log)
        : r(regex), input(input), output(output), log(log) {}

void Match::operator()() {
    while (!input->isAtEnd()) {
        string s = input->pop();
        string message = s + " -> ";
        if (regex_search(s, r)) {
            message += s;
            output->push(s);
        } else {
            message += "(Filtrado)";
        }
        if (log) log->push(message);
    }
    output->close();
    if (log) log->close();
}
