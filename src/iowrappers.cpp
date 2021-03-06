#include "iowrappers.h"
#include <iostream>
#include <string>

using namespace std;

string StdinWrapper::pop() {
    string x;
    getline(cin, x);
    return x;
}

bool StdinWrapper::isAtEnd() {
    return cin.peek() == EOF;
}

void StdoutWrapper::push(const string &x) {
    cout << x << endl;
}

void StdoutWrapper::close() {}
