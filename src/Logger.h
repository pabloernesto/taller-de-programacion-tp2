#include <string>
#include <vector>
#include <mutex>
#include "SourceSink.h"

#ifndef LOGGER_H
#define LOGGER_H

class Log : public Sink {
    std::string name;
    std::vector<std::string> messages;
    std::mutex m;
public:
    Log(std::string name);
    void push(const std::string &x);
    void close();
    void print();
    std::string getName();
};

class Logger {
    std::vector<Log*> logs;
    std::mutex m;

    public:
    Log* requestLog(const std::string &name);
    void print();
    void clear();
};

#endif
