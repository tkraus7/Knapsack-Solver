#include <iostream>
#include <vector>
#include <fstream>

#include "knapsack.h"

using namespace std;

Knapsack *readFromFile(ifstream &in) {
    int maxWeight, numOfWeights;
    in >> maxWeight >> numOfWeights;
    Knapsack *k = new Knapsack(maxWeight, numOfWeights);

    int weight, cost;
    for (int i = 0; i < numOfWeights; i++) {
        in >> weight >> cost;
        k->WEIGHTS[i][0] = weight;
        k->WEIGHTS[i][1] = cost;
    }

    cout << "weight: " << maxWeight << " numWeights: " << numOfWeights << endl;
    for (int i = 0; i < numOfWeights; i++) {
        cout << k->WEIGHTS[i][0] << " " << k->WEIGHTS[i][1] << endl;
    }

    return k;
}

int main(int argc, char **argv) {
    Knapsack *k = nullptr;

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

            ifstream file(argv[++i]);
            if (!file.good()) {
                cerr << "ERROR: File not found: " << argv[i] << endl;
                return 1;
            }
            k = readFromFile(file);
        } else {
            cout << "ERROR: Unknown command line argument: " << arg << endl;
            cout << "Try '-h' or '--help' for more information." << endl;
            return 0;
        }
    }

    if (k) {
        solveKnapsackSingle(k);
        delete k;
    } else {
        cout << helpText << endl;
    }

    return 0;
}
