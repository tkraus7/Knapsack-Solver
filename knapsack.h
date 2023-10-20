#ifndef PCC_SEMESTRAL_PROJECT_KNAPSACK_H
#define PCC_SEMESTRAL_PROJECT_KNAPSACK_H

#include <vector>

inline const char *helpText =
        "Usage: ./KnapsackSolver [OPTION]...\n"
        "Find the optimal solution for knapsack problem 0-1.\n"
        "\n"
        "   -f, --file [FILENAME]   read input data from file\n"
        "   -h, --help              show this message\n"
        "   -p, --parallel          run the multi-threaded version of this program\n"
        "\n"
        "Examples:\n"
        "   ./KnapsackSolver -f ../data/pub01.in    Find optimal solution for knapsack problem described in\n"
        "                                           file ../data/pub01.in.\n"
        "   ./KnapsackSolver -p                     Use standard input for problem description and solve it\n"
        "                                           using multiple threads.\n";

class Knapsack {
public:
    int maxWeight;
    int numOfWeights;
    int optCost;
    std::vector<std::pair<int, int>> solution;

    virtual void solveKnapsack() = 0;

    virtual void backtrackSolution() = 0;

    virtual void printKnapsack() = 0;

    virtual void printSolution() = 0;

    virtual ~Knapsack() {}
};


#endif //PCC_SEMESTRAL_PROJECT_KNAPSACK_H
