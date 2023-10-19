#ifndef PCC_SEMESTRAL_PROJECT_KNAPSACK_H
#define PCC_SEMESTRAL_PROJECT_KNAPSACK_H

class Knapsack {
    int** KNAPSACK;
    int maxWeight;
    int numOfWeights;

public:
    Knapsack(int knapsackWeight, int numOfWeights) : maxWeight(knapsackWeight), numOfWeights(numOfWeights) {
        KNAPSACK = new int*[numOfWeights];
        for (int i = 0; i < numOfWeights; i++) {
            KNAPSACK[i] = new int[knapsackWeight];
        }
    }

    void backtrackSolution();

    ~Knapsack() {
        for (int i = 0; i < numOfWeights; i++) {
            delete[] KNAPSACK[i];
        }
        delete[] KNAPSACK;
    }
};


void solveKnapsackSingle();
void solveKnapsackParallel();

#endif //PCC_SEMESTRAL_PROJECT_KNAPSACK_H
