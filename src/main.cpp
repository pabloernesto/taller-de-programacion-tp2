#include <stdlib.h>
#include <getopt.h>
#include <vector>
#include <string>
#include <iostream>
#include <thread>

#include "BoundedBuffer.h"
#include "iowrappers.h"
#include "tasks.h"
#include "Logger.h"

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

    /* optind is the index in argv of the first argv-element that is not
     * an option. argc - optind is the number of elements in argv that are not
     * options. */
    vector<struct command> commands;
    parseCommands(argc - optind, argv + optind, commands);

    // If there are no commands, fail.
    if (commands.size() == 0) return 1;

    vector<BoundedBuffer> buffers(commands.size() - 1);
    vector<std::thread> threads;

    StdinWrapper in;
    StdoutWrapper out;

    Logger log_factory;

    for (unsigned int i = 0; i < commands.size(); i++) {
        Source *source;
        if (i == 0) source = &in;
        else
            source = &(buffers[i - 1]);

        Sink *sink;
        if (i == (commands.size() - 1)) sink = &out;
        else
            sink = &(buffers[i]);

        if (commands[i].operation == "echo") {
            Log *log = nullptr;
            if (debug_mode) log = log_factory.requestLog("echo");

            Echo t(source, sink, log);

            threads.emplace_back(std::move(t));
        } else if (commands[i].operation == "match") {
            Log *log = nullptr;
            if (debug_mode) log = log_factory.requestLog("match");

            Match t(commands[i].regex, source, sink, log);

            threads.emplace_back(std::move(t));
        } else if (commands[i].operation == "replace") {
            Log *log = nullptr;
            if (debug_mode) log = log_factory.requestLog("replace");

            Replace t(commands[i].regex, std::move(commands[i].replacement),
                    source, sink, log);

            threads.emplace_back(std::move(t));
        }
    }

    for (unsigned int i = 0; i < threads.size(); i++) threads[i].join();

    log_factory.print();
    log_factory.clear();
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
