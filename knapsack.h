#ifndef PCC_SEMESTRAL_PROJECT_KNAPSACK_H
#define PCC_SEMESTRAL_PROJECT_KNAPSACK_H

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
    int **KNAPSACK;
    int **WEIGHTS;
    int maxWeight;
    int numOfWeights;

    Knapsack();

    Knapsack(int knapsackWeight, int totalNumOfWeights) : maxWeight(knapsackWeight), numOfWeights(totalNumOfWeights) {
        KNAPSACK = new int *[totalNumOfWeights];
        WEIGHTS = new int *[totalNumOfWeights];
        for (int i = 0; i < totalNumOfWeights; i++) {
            KNAPSACK[i] = new int[knapsackWeight + 1]();
            WEIGHTS[i] = new int[2];
        }
    }

    void backtrackSolution();

    ~Knapsack() {
        for (int i = 0; i < numOfWeights; i++) {
            delete[] KNAPSACK[i];
            delete[] WEIGHTS[i];
        }
        delete[] KNAPSACK;
        delete[] WEIGHTS;
    }
};

void solveKnapsackSingle(Knapsack *k);

//void solveKnapsackParallel(Knapsack &k);

#endif //PCC_SEMESTRAL_PROJECT_KNAPSACK_H
