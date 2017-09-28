#include "Match.hpp"
#include <string>
#include <regex>

using namespace std;

Match::Match(std::string regex, Source &input, Sink &output)
        : r(regex), input(input), output(output) {}

void Match::operator()() {
    while (!input.isAtEnd()) {
        string s = input.pop();
        if (s != "a")
            output.push(s);
    }
    output.close();
}

