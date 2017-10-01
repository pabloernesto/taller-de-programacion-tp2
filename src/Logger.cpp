#include "Logger.hpp"
#include <iostream>

using namespace std;

std::vector<Log> Logger::logs;

Sink& Logger::requestLog(string name) {
    unique_lock<mutex> lck{Logger::m};
    //posfix the name
    Log l{name};
    Logger::logs.push_back(l);
    return logs.back();
}

void Logger::print() {
    unique_lock<mutex> lck{Logger::m};
    for (unsigned int i = 0; i < Logger::logs.size(); i++)
        Logger::logs[i].print();
}

void Logger::clear() {
    unique_lock<mutex> lck{Logger::m};
    Logger::logs.clear();
}

Log::Log(string name) : name(name), messages(), closed(false), m() {}

void Log::push(string x) {
    unique_lock<mutex> lck{this->m};
    if (this->closed) throw;
    this->messages.push_back(x);
}

void Log::close() {
    unique_lock<mutex> lck{this->m};
    this->closed = true;
}

void Log::print() {
    unique_lock<mutex> lck{this->m};
    for (unsigned int i = 0; i < this->messages.size(); i++)
        cerr << this->messages[i];
}
