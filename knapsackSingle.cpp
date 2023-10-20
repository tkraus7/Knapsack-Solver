#include "knapsackSingle.h"

#include <iostream>

const int &max(const int &a, const int &b) {
    return a < b ? b : a;
}

int worseMax(int a, int b) {
    return a < b ? b : a;
}

void KnapsackSingle::allocateSpace(int knapsackWeight, int totalNumOfWeights) {
    maxWeight = knapsackWeight;
    numOfWeights = totalNumOfWeights;
    KNAPSACK = new int *[totalNumOfWeights];
    WEIGHTS = new int *[totalNumOfWeights];
    for (int i = 0; i < totalNumOfWeights; i++) {
        KNAPSACK[i] = new int[knapsackWeight + 1]();
        WEIGHTS[i] = new int[2];
    }
}

KnapsackSingle::KnapsackSingle(int knapsackWeight, int totalNumOfWeights) {
    allocateSpace(knapsackWeight, totalNumOfWeights);
}

KnapsackSingle::KnapsackSingle(std::ifstream &in) {
    int maxWeight, numOfWeights;
    in >> maxWeight >> numOfWeights;
    allocateSpace(maxWeight, numOfWeights);

    int weight, cost;
    for (int i = 0; i < numOfWeights; i++) {
        in >> weight >> cost;
        WEIGHTS[i][0] = weight;
        WEIGHTS[i][1] = cost;
    }
}

void KnapsackSingle::solveKnapsack() {
    for (int i = WEIGHTS[0][0]; i <= maxWeight; i++) {
        KNAPSACK[0][i] = WEIGHTS[0][1];
    }

    for (int i = 1; i < numOfWeights; i++) {
        for (int j = 1; j <= maxWeight; j++) {
            if (j >= WEIGHTS[i][0]) {
                KNAPSACK[i][j] = max(KNAPSACK[i - 1][j],
                                     WEIGHTS[i][1] + KNAPSACK[i - 1][j - WEIGHTS[i][0]]);
            } else {
                KNAPSACK[i][j] = KNAPSACK[i - 1][j];
            }
        }
    }
}

void KnapsackSingle::backtrackSolution() {
    int i = numOfWeights - 1, j = maxWeight;
    optCost = KNAPSACK[i][j];

    int current;
    while (i != 0) {
        current = KNAPSACK[i][j];
        if (current == 0) {
            break;
        } else if (KNAPSACK[i - 1][j] == current) {
            i--;
        } else {
            solution.push_back(std::pair<int, int>(WEIGHTS[i][0], WEIGHTS[i][1]));
            j -= WEIGHTS[i][0];
            i--;
        }
    }
    if (current != 0 && j != 0) {
        solution.push_back(std::pair<int, int>(WEIGHTS[0][0], WEIGHTS[0][1]));
    }

}

void KnapsackSingle::printKnapsack() {
    for (int i = 0; i < numOfWeights; i++) {
        for (int j = 0; j <= maxWeight; j++) {
            std::cout << KNAPSACK[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void KnapsackSingle::printSolution() {
    std::cout << optCost << " " << solution.size() << std::endl;
    for (auto p: solution) {
        std::cout << p.first << " " << p.second << std::endl;
    }
}

void KnapsackSingle::printSolutionVerbose() {
    std::cout << "---------------------------------------------\n";
    std::cout << "optimal cost: " << optCost << "\nnumber of weights used: " << solution.size() << std::endl;
    std::cout << "---------------------------------------------\n";
    std::cout << "weight\t\tcost\n";
    for (auto p: solution) {
        std::cout << p.first << "\t\t" << p.second << std::endl;
    }
    std::cout << "---------------------------------------------\n";
}

KnapsackSingle::~KnapsackSingle() {
    for (int i = 0; i < numOfWeights; i++) {
        delete[] KNAPSACK[i];
        delete[] WEIGHTS[i];
    }
    delete[] KNAPSACK;
    delete[] WEIGHTS;
}
