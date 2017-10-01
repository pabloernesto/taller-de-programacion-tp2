#ifndef _GNU_SOURCE
    #define _GNU_SOURCE
#endif

#include <stdlib.h>
#include <getopt.h>
#include <vector>
#include <string>
#include <iostream>
#include <thread>

#include "BoundedBuffer.hpp"
#include "iowrappers.hpp"
#include "tasks.hpp"
#include "Logger.hpp"

using namespace std;

struct command {
    string operation;
    string regex;
    string replacement;
};

static void processOptions(int argc, char **argv);
static void printUsage();
static void parseCommands(int argc, char **argv,
                          vector<struct command> &output);

static int debug_mode = 0;

int main(int argc, char **argv) {
    processOptions(argc, argv);
    cout << "debug mode: " << (debug_mode ? "ON" : "OFF") << endl;

    /* optind is the index in argv of the first argv-element that is not
     * an option. argc - optind is the number of elements in argv that are not
     * options. */
    vector<struct command> commands;
    parseCommands(argc - optind, argv + optind, commands);

    // If there are no commands, fail.
    if (commands.size() == 0) return 1;

    vector<BoundedBuffer> buffers(commands.size() - 1);
    vector<Task*> tasks;
    vector<std::thread> threads;

    StdinWrapper in;
    StdoutWrapper out;

    for (unsigned int i = 0; i < commands.size(); i++) {
        Source *source;
        if (i == 0) source = &in;
        else source = &(buffers[i - 1]);

        Sink *sink;
        if (i == (commands.size() - 1)) sink = &out;
        else sink = &(buffers[i]);

        if (commands[i].operation == "echo") {
            Echo *t = new Echo(source, sink);
            tasks.push_back(t);
            threads.emplace_back(*t);
        } else if (commands[i].operation == "match") {
            Match *t = new Match(commands[i].regex, source, sink);
            tasks.push_back(t);
            threads.emplace_back(*t);
        } else if (commands[i].operation == "replace") {
            Replace *t = new Replace(commands[i].regex, commands[i].replacement,
                                     source, sink);
            tasks.push_back(t);
            threads.emplace_back(*t);
        }
    }

    for (unsigned int i = 0; i < tasks.size(); i++) threads[i].join();
    while (tasks.size() != 0) { delete tasks.back(); tasks.pop_back(); }

    if (debug_mode) Logger::print();
    Logger::clear();
}

static void processOptions(int argc, char **argv) {
    int c;
    opterr = 0; // Mute getopt's error messages.
    while (1) {
        int option_index = 0;
        static struct option long_options[] = {
            { "input",  required_argument,  0,  'i' },
            { "output", required_argument,  0,  'o' },
            { "debug",  no_argument,        0,  'd' },
            { 0,        0,                  0,   0  }
        };

        c = getopt_long(argc, argv, "i:o:d", long_options, &option_index);

        if (c == -1) {
            break;
        } else if (c == 'i') {
            if (freopen(optarg, "r", stdin) == NULL) {
                cerr << "Could not open " << optarg << endl;
                exit(1);
            }
        } else if (c == 'o') {
            if (freopen(optarg, "w", stdout) == NULL) {
                cerr << "Could not open " << optarg << endl;
                exit(1);
            }
        } else if (c == 'd') {
            debug_mode = 1;
        } else {
            printUsage();
            exit(1);
        }
    }
}

static void printUsage() {
    cout << "tp [--input filename] [--output filename] [--debug] "
            "cmd [:: cmd]..." << endl;
}

static void parseCommands(int argc, char **argv,
                          vector<struct command> &output) {
    for (; argc > 0; argc--, argv++) {
        /* Note the implicit conversion from *char to string */
        struct command c = { *argv };

        if (c.operation == "echo") {
        } else if (c.operation == "match") {
            if (argc < 2) {
                cerr << "Insufficient arguments for match: "
                     << c.operation << endl;
                exit(1);
            }
            c.regex = *(++argv);
            argc--;
        } else if (c.operation == "replace") {
            if (argc < 3) {
                cerr << "Insufficient arguments for replace: "
                     << c.operation << endl;
                exit(1);
            }
            c.regex = *(++argv);
            c.replacement = *(++argv);
            argc -= 2;
        } else {
            cerr << "Unrecognized command: " << c.operation << endl;
            exit(1);
        }

        /* Handle the command separator (::) */
        if (argc > 1) {
            argc--;
            string s(*(++argv));
            if (s != "::") {
                cerr << "Missing '::' after " << c.operation
                     << " terminating." << endl;
                exit(1);
            }
        }

        output.push_back(c);
    }
}
