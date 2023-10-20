#ifndef PCC_SEMESTRAL_PROJECT_KNAPSACK_H
#define PCC_SEMESTRAL_PROJECT_KNAPSACK_H

#include <vector>
#include <fstream>

inline const char *helpText =
        "Usage: ./KnapsackSolver [OPTION]...\n"
        "Find the optimal solution for knapsack problem 0-1.\n"
        "\n"
        "   -f, --file [FILENAME]       read input data from file\n"
        "   -g, --generate              generate input data\n"
        "   -h, --help                  show this message\n"
        "   -p, --parallel [NUMBER]     run the multi-threaded version of this program using the specified\n"
        "                               number of threads\n"
        "   -v, --verbose               print the verbose version of the solution\n"
        "\n"
        "Examples:\n"
        "   ./KnapsackSolver -f pub01.in\n"
        "   ./KnapsackSolver -p 5 -f pub03.in -v\n";


class Knapsack {
    int optCost;
    std::vector<std::pair<int, int>> solution;

    void allocateSpace(int knapsackWeight, int totalNumOfWeights);
    int sumWeight() {
        int res = 0;
        for (auto p: solution) {
            res += p.first;
        }
        return res;
    }

public:
    int maxWeight;
    int numOfWeights;

    int **KNAPSACK;
    int **WEIGHTS;

    Knapsack(std::ifstream &in);

    virtual void solveKnapsack() = 0;

    void backtrackSolution();

    void printKnapsack();

    void printSolution();

    void printSolutionVerbose();

    const int &max(const int &a, const int &b) {
        return a < b ? b : a;
    }

    int worseMax(int a, int b) {
        return a < b ? b : a;
    }

    ~Knapsack();
};


#endif //PCC_SEMESTRAL_PROJECT_KNAPSACK_H
