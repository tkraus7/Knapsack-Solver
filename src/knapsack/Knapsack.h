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
    unsigned int optCost;
    std::vector<std::pair<unsigned int, unsigned int>> solution;

    /**
     * Allocates space for the main table and the array holding the information about weights.
     * @param knapsackWeight maximal weight of the knapsack
     * @param totalNumOfWeights the total number of available weights
     */
    void allocateSpace(unsigned int knapsackWeight, unsigned int totalNumOfWeights);

    int sumWeight() {
        int res = 0;
        for (auto p: solution) {
            res += p.first;
        }
        return res;
    }

public:
    unsigned int maxWeight;
    unsigned int numOfWeights;

    /**
     * A 2D-array used for the main computation.
     */
    unsigned int **KNAPSACK;

    /**
     * A 2D-array holding the information about available weights.
     */
    unsigned int **WEIGHTS;

    /**
     * Constructs the Knapsack based on the data stored in a file.
     * @param in stream from the data file
     */
    explicit Knapsack(std::ifstream &in);

    /**
     * Runs the algorithm and fills up the KNAPSACK table.
     */
    virtual void solveKnapsack() = 0;

    /**
     * Gets the optimal solution and finds the weights used.
     */
    void backtrackSolution();

    void printKnapsack();

    /**
     *  Prints the solution in a simple format.
     */
    void printSolution();

    /**
     * Prints the solution in a verbose format.
     */
    void printSolutionVerbose();

    static const unsigned int &max(const unsigned int &a, const unsigned int &b) {
        return a < b ? b : a;
    }

    static const unsigned int &min(const unsigned int &a, const unsigned int &b) {
        return a > b ? b : a;
    }

    ~Knapsack();
};


#endif //PCC_SEMESTRAL_PROJECT_KNAPSACK_H
