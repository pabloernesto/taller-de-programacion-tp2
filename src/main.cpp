#ifndef _GNU_SOURCE
    #define _GNU_SOURCE
#endif

#include <stdlib.h>
#include <getopt.h>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

int debug_mode = 0;

struct command {
    string operation;
    string regex;
    string replacement;
};

static void processOptions(int argc, char **argv);
static void printUsage();
static void parseCommands(int argc, char **argv,
                          vector<struct command> &output);

int main(int argc, char **argv) {
    processOptions(argc, argv);
    cout << "debug mode: " << (debug_mode ? "ON" : "OFF") << endl;

    /* optind is the index in argv of the first argv-element that is not
     * an option. argc - optind is the number of elements in argv that are not
     * options. */
    vector<struct command> commands;
    parseCommands(argc - optind, argv + optind, commands);
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
            cout << "echo" << endl;
        } else if (c.operation == "match") {
            if (argc < 2) {
                cerr << "Insufficient arguments for match: "
                     << c.operation << endl;
                exit(1);
            }
            c.regex = *(++argv);
            argc--;
            cout << c.regex << endl;
        } else if (c.operation == "replace") {
            if (argc < 3) {
                cerr << "Insufficient arguments for replace: "
                     << c.operation << endl;
                exit(1);
            }
            c.regex = *(++argv);
            c.replacement = *(++argv);
            argc -= 2;
            cout << "regex " << c.regex << " replace " << c.replacement << endl;
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
    }
}
