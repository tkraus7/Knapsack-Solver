#ifndef PCC_SEMESTRAL_PROJECT_KNAPSACKPARALLEL_H
#define PCC_SEMESTRAL_PROJECT_KNAPSACKPARALLEL_H

#include <thread>
#include <list>
#include <mutex>
#include <condition_variable>
#include "Knapsack.h"

class KnapsackParallel : public Knapsack {
    int numOfThreads;
    int currentlyWorking;

    std::thread supportThread;
    std::vector<std::thread> threadPool;
    std::list<std::tuple<int, int, int>> queue;

    std::mutex queue_mu;
    std::condition_variable cv;

    void worker(std::tuple<int, int, int> job) ;
    void joinAll();
public:
    KnapsackParallel(std::ifstream &in, int numOfThreads);

    void solveKnapsack();
};


#endif //PCC_SEMESTRAL_PROJECT_KNAPSACKPARALLEL_H
