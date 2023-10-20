#include "KnapsackSingle.h"



KnapsackSingle::KnapsackSingle(std::ifstream &in) : Knapsack(in) {}

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



