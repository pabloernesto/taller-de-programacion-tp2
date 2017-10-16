#include "Logger.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

Log* Logger::requestLog(const string &name) {
    unique_lock<mutex> lck(m);

    int n = 1;
    for (unsigned int i = 0; i < logs.size(); i++)
        if (logs[i]->getName() == name + to_string(n)) n++;

    logs.push_back(new Log(name + to_string(n)));
    return logs.back();
}

void Logger::print() {
    unique_lock<mutex> lck(m);

    if (logs.size() == 0) return;

    cerr << "(" << 1 << ") ";
    logs[0]->print();
    for (unsigned int i = 1; i < logs.size(); i++) {
        cerr << endl;
        cerr << "(" << i + 1 << ") ";
        logs[i]->print();
    }
}

void Logger::clear() {
    unique_lock<mutex> lck(m);
    for (unsigned int i = 0; i < logs.size(); i++)
        delete logs[i];
    logs.clear();
}

Log::Log(string name) : name(name), messages(), m() {}

void Log::close() {}

void Log::push(const string &x) {
    unique_lock<mutex> lck{this->m};
    this->messages.push_back(x);
}

void Log::print() {
    unique_lock<mutex> lck{this->m};
    cerr << this->name << endl;
    for (unsigned int i = 0; i < this->messages.size(); i++)
        cerr << this->messages[i] << endl;
}

std::string Log::getName() {
    return this->name;
}
