#ifndef PCC_SEMESTRAL_PROJECT_KNAPSACKSINGLE_H
#define PCC_SEMESTRAL_PROJECT_KNAPSACKSINGLE_H

#include <fstream>
#include "knapsack.h"


class KnapsackSingle : public Knapsack {
    int **KNAPSACK;
    int **WEIGHTS;

    void allocateSpace(int knapsackWeight, int totalNumOfWeights);

public:
    KnapsackSingle(int knapsackWeight, int totalNumOfWeights);

    KnapsackSingle(std::ifstream &in);

    void solveKnapsack();

    void backtrackSolution();

    void printKnapsack();

    void printSolution();

    ~KnapsackSingle();
};

#endif //PCC_SEMESTRAL_PROJECT_KNAPSACKSINGLE_H
