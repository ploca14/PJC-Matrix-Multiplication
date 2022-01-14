
#include "cli.h"
#include "string"

int main(int argc, char *argv[]) {
    if (argc > 1) {
        std::string cmd = argv[1];
        if (cmd == "--help") {
            print_help();
        } else if (cmd == "--random") {
            random_multipy();
        }
    } else {
        user_multiply();
    }

    return 0;
}

