#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>

#include "Knapsack.h"
#include "KnapsackSingle.h"
#include "KnapsackParallel.h"

using namespace std;

template <typename TimePoint>
std::chrono::milliseconds to_ms(TimePoint tp) {
    return std::chrono::duration_cast<std::chrono::milliseconds>(tp);
}

void run(Knapsack &k, bool verbose) {
    auto start = std::chrono::high_resolution_clock::now();
    k.solveKnapsack();
    k.backtrackSolution();
    auto end = std::chrono::high_resolution_clock::now();

//    k.printKnapsack();

    if (verbose) {
        k.printSolutionVerbose();
    } else {
        k.printSolution();
    }
    cout << "Computation took: " << to_ms(end - start).count() << " ms" << endl;
}

int main(int argc, char **argv) {
    ifstream file;
    bool useThreads = false, useVerbose = false;
    int numOfThreads;

    if (argc == 1) {
        cout << helpText << endl;
        return 0;
    }

    for (int i = 1; i < argc; i++) {
        string arg(argv[i]);
        if (arg == "-h" || arg == "--help") {
            cout << helpText << endl;
            return 0;
        } else if (arg == "-p" || arg == "--parallel") {
            std::cout << "Running program with multiple threads\n";
            if (i + 1 >= argc) {
                cerr << "ERROR: Number of threads not specified" << endl;
                return 1;
            }
            numOfThreads = atoi(argv[++i]);
            if (numOfThreads == 0) {
                cerr << "ERROR: Bad value:" << argv[i] << endl;
                return 1;
            }
            useThreads = true;
        } else if (arg == "-v" || arg == "--verbose") {
            useVerbose = true;
        } else if (arg == "-f" || arg == "--file") {
            if (i + 1 >= argc) {
                cerr << "ERROR: No file specified" << endl;
                return 1;
            }
            file = ifstream(argv[++i]);
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


    if (useThreads) {
        KnapsackParallel k(file, numOfThreads);
        run(k, useVerbose);
    } else {
        KnapsackSingle k(file);
        run(k, useVerbose);
    }

    return 0;
}
