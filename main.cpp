
#include "cli.h"
#include "string"

int main(int argc, char *argv[]) {
    if (argc > 1) {
        std::string cmd = argv[1];
        if (cmd == "--help") {
            print_help();
        } else if (cmd == "--random") {
            if (argc > 2) {
                long int size = strtol(argv[2], NULL, 10);
                random_multiply(size);
            } else {
                random_multiply(0);
            }
        }
    } else {
        std::cout << "MATRIX MULTIPLICATION" << std::endl << std::endl;
        char answer = 'N';
        do {
            user_multiply();

            std::cout << std::endl << "Do you want to continue with more matrices? (Y/N): ";
            std::cin >> answer;
        } while (answer == 'Y' || answer == 'y');
    }
    return 0;
}

