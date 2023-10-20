#ifndef PCC_SEMESTRAL_PROJECT_KNAPSACKSINGLE_H
#define PCC_SEMESTRAL_PROJECT_KNAPSACKSINGLE_H

#include <fstream>
#include "Knapsack.h"


class KnapsackSingle : public Knapsack {

public:
//    KnapsackSingle(int knapsackWeight, int totalNumOfWeights);

    KnapsackSingle(std::ifstream &in);

    void solveKnapsack();
};

#endif //PCC_SEMESTRAL_PROJECT_KNAPSACKSINGLE_H
