#include "knapsack.h"

#include <iostream>

const int &max(const int &a, const int &b) {
    return a < b ? b : a;
}

int worseMax(int a, int b) {
    return a < b ? b : a;
}

void solveKnapsackSingle(Knapsack *k) {
    for (int i = k->WEIGHTS[0][0]; i <= k->maxWeight; i++) {
        k->KNAPSACK[0][i] = k->WEIGHTS[0][1];
    }


    for (int i = 1; i < k->numOfWeights; i++) {
        for (int j = 1; j <= k->maxWeight; j++) {
            if (j >= k->WEIGHTS[i][0]) {
                k->KNAPSACK[i][j] = max(k->KNAPSACK[i - 1][j],
                                        k->WEIGHTS[i][1] + k->KNAPSACK[i - 1][j - k->WEIGHTS[i][0]]);
            } else {
                k->KNAPSACK[i][j] = k->KNAPSACK[i - 1][j];
            }

        }
    }

    for (int i = 0; i < k->numOfWeights; i++) {
        for (int j = 0; j <= k->maxWeight; j++) {
            std::cout << k->KNAPSACK[i][j] << " ";
        }
        std::cout << std::endl;
    }

}