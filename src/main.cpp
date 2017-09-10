#ifndef _GNU_SOURCE
    #define _GNU_SOURCE
#endif

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

int debug_mode = 0;

static void processOptions(int argc, char **argv);
static void printUsage();

int main(int argc, char **argv) {
    processOptions(argc, argv);

    /* optind is the index in argv of the first argv-element that is not
     * an option */
    //~ struct command *commands = parseCommands(argc - optind, argv + optind);

    printf("debug mode: %s\n", debug_mode ? "ON" : "OFF");
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
                fprintf(stderr, "Could not open %s", optarg);
                exit(1);
            }
        } else if (c == 'o') {
            if (freopen(optarg, "w", stdout) == NULL) {
                fprintf(stderr, "Could not open %s", optarg);
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
    printf("tp [--input filename] [--output filename] [--debug] "
           "cmd [:: cmd]...\n");
}
