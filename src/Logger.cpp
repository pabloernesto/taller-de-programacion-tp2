#include "Logger.hpp"
#include <iostream>

using namespace std;

vector<Log*> Logger::logs;
mutex Logger::m;

Sink* Logger::requestLog(string name) {
    unique_lock<mutex> lck{Logger::m};
    //posfix the name
    Logger::logs.push_back(new Log(name));
    return logs.back();
}

void Logger::print() {
    unique_lock<mutex> lck{Logger::m};
    for (unsigned int i = 0; i < Logger::logs.size(); i++)
        Logger::logs[i]->print();
}

void Logger::clear() {
    unique_lock<mutex> lck{Logger::m};
    for (unsigned int i = 0; i < Logger::logs.size(); i++)
        delete Logger::logs[i];
    Logger::logs.clear();
}

Log::Log(string name) : name(name), messages(), m() {}

void Log::close() {}

void Log::push(string x) {
    unique_lock<mutex> lck{this->m};
    this->messages.push_back(x);
}

void Log::print() {
    unique_lock<mutex> lck{this->m};
    for (unsigned int i = 0; i < this->messages.size(); i++)
        cerr << this->messages[i] << endl;
}
