#ifndef PCC_SEMESTRAL_PROJECT_KNAPSACKSINGLE_H
#define PCC_SEMESTRAL_PROJECT_KNAPSACKSINGLE_H

#include <fstream>
#include "../knapsack/Knapsack.h"


class KnapsackSingle : public Knapsack {

public:

    KnapsackSingle(std::ifstream &in);

    void solveKnapsack() override;
};

#endif //PCC_SEMESTRAL_PROJECT_KNAPSACKSINGLE_H
