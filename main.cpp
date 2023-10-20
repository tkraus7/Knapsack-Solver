#include <iostream>
#include <vector>
#include <fstream>

#include "knapsack.h"
#include "knapsackSingle.h"

using namespace std;


int main(int argc, char **argv) {
    ifstream file;

    for (int i = 1; i < argc; i++) {
        string arg(argv[i]);
        if (arg == "-h" || arg == "--help") {
            cout << helpText << endl;
            return 0;
        } else if (arg == "-p" || arg == "--parallel") {
            cout << "Running program with multiple threads" << endl;
        } else if (arg == "-f" || arg == "--file") {
            if (i + 1 >= argc) {
                cerr << "ERROR: No file specified" << endl;
                return 1;
            }

            file = ifstream (argv[++i]);
            if (!file.good()) {
                cerr << "ERROR: File not found: " << argv[i] << endl;
                return 1;
            }
        } else {
            cout << "ERROR: Unknown command line argument: " << arg << endl;
            cout << "Try '-h' or '--help' for more information." << endl;
            return 0;
        }
    }

    KnapsackSingle k(file);

    k.solveKnapsack();
    k.backtrackSolution();
    k.printSolution();

    return 0;
}
