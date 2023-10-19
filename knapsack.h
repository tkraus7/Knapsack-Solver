#ifndef PCC_SEMESTRAL_PROJECT_KNAPSACK_H
#define PCC_SEMESTRAL_PROJECT_KNAPSACK_H

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
