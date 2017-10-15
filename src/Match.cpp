#include "tasks.h"
#include "Logger.h"
#include <string>
#include <regex>

using namespace std;

Match::Match(std::string regex, Source *input, Sink *output)
        : r(regex), input(input), output(output) {}

void Match::operator()() {
    Sink *log = Logger::requestLog("match");
    while (!input->isAtEnd()) {
        string s = input->pop();
        string message = s + " -> ";
        if (regex_search(s, r)) {
            message += s;
            output->push(s);
        } else {
            message += "(Filtrado)";
        }
        log->push(message);
    }
    output->close();
}
