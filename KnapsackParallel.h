#ifndef PCC_SEMESTRAL_PROJECT_KNAPSACKPARALLEL_H
#define PCC_SEMESTRAL_PROJECT_KNAPSACKPARALLEL_H

#include <thread>
#include <list>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include "Knapsack.h"

class KnapsackParallel : public Knapsack {
    int numOfThreads;
    std::atomic<int> currentlyWorking;

    std::thread supportThread;
    std::vector<std::thread> threadPool;
    std::list<std::tuple<int, int, int>> queue;

    std::mutex queueMu, workingMu;
    std::condition_variable queueCv, workingCv;

    void worker(std::tuple<int, int, int> job) ;
    void joinAll();
public:
    KnapsackParallel(std::ifstream &in, int numOfThreads);

    void solveKnapsack();
};


#endif //PCC_SEMESTRAL_PROJECT_KNAPSACKPARALLEL_H
