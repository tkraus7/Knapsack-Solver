#ifndef PCC_SEMESTRAL_PROJECT_KNAPSACKPARALLEL_H
#define PCC_SEMESTRAL_PROJECT_KNAPSACKPARALLEL_H

#include <thread>
#include <list>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include "../knapsack/Knapsack.h"

class KnapsackParallel : public Knapsack {
    int numOfThreads;

    /**
     * Variable showing the number of currently working threads. If its zero, then work
     * on a new row can be started.
     */
    std::atomic<int> currentlyWorking;

    /**
     * Helper thread that fills up the work queue every time a row is finished.
     */
    std::thread supportThread;

    /**
     * Vector holding all the worker threads.
     */
    std::vector<std::thread> threadPool;

    /**
     * Queue of available jobs for threads.
     */
    std::list<std::tuple<int, int, int>> queue;

    /**
     * Mutex guarding the job queue.
     */
    std::mutex queueMu;
    std::condition_variable queueCv, workingCv;

    /**
     * Helper function that fills up small part of KNAPSACK table described in job.
     * @param job tuple containing information about row, start and end of work to be done
     */
    void worker(std::tuple<int, int, int> job);

public:
    /**
     * Constructs the Knapsack based on the data stored in a file.
     * @param in stream from the data file
     * @param numOfThreads maximum number of threads that can be used
     */
    KnapsackParallel(std::ifstream &in, int numOfThreads);

    void solveKnapsack() override;
};


#endif //PCC_SEMESTRAL_PROJECT_KNAPSACKPARALLEL_H
