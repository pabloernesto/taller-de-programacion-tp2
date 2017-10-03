#include <string>
#include <vector>
#include <mutex>
#include "SourceSink.hpp"

#ifndef LOGGER_H
#define LOGGER_H

class Log : public Sink {
    std::string name;
    std::vector<std::string> messages;
    std::mutex m;
public:
    Log(std::string name);
    void push(std::string x);
    void close();
    void print();
    std::string getName();
};

class Logger {
    static std::vector<Log*> logs;
    static std::mutex m;
public:
    static Sink* requestLog(std::string name);
    static void print();
    static void clear();
};

#endif
