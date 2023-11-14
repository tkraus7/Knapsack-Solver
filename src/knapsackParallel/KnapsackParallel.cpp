#include <cmath>
#include <iostream>
#include "KnapsackParallel.h"

#define MINIMAL_THREAD_JOB_SIZE 5

KnapsackParallel::KnapsackParallel(std::ifstream &in, int numOfThreads) :
        Knapsack(in),
        numOfThreads(numOfThreads),
        currentlyWorking(0) {}

void KnapsackParallel::worker(std::tuple<unsigned int, unsigned int, unsigned int> job) {
    auto [row, begin, end] = job;
    for (; begin < end; begin++) {
        if (begin >= WEIGHTS[row][0]) {
            KNAPSACK[row][begin] = max(KNAPSACK[row - 1][begin],
                                       WEIGHTS[row][1] + KNAPSACK[row - 1][begin - WEIGHTS[row][0]]);
        } else {
            KNAPSACK[row][begin] = KNAPSACK[row - 1][begin];
        }
    }
}

/**
 * Solves the 0-1 knapsack problem using multiple threads. Each row of the KNAPSACK table
 * is divided equally amongst the worker threads. Once they're all finished, work on a next
 * row is started.
 */
void KnapsackParallel::solveKnapsack() {
    /// first row is filled manually in the main thread
    for (unsigned int i = WEIGHTS[0][0]; i <= maxWeight; i++) {
        KNAPSACK[0][i] = WEIGHTS[0][1];
    }

    /// checks if there is a reasonable number of threads for the given task
    /// e.g. the size of a single job is at least equal to MINIMAL_THREAD_JOB_SIZE
    int numOfWorkers = (maxWeight / numOfThreads) >= MINIMAL_THREAD_JOB_SIZE ? numOfThreads : 1;

    /// calculates the size of a single job
    int oneThreadWork = std::round(maxWeight / numOfWorkers) + 1;

    /// creates the support thread that creates jobs and feeds them to the job queue
    supportThread = std::thread([&]() {
        for (unsigned int i = 1; i <= numOfWeights; i++) {
            std::unique_lock<std::mutex> queueLock(queueMu);

            /// waits until there are no threads working
            workingCv.wait(queueLock, [&] { return currentlyWorking == 0; });

            /// then adds new jobs to the job queue
            for (int j = 0; j < numOfWorkers; j++) {
                currentlyWorking++;
                queue.emplace_back(i, j * oneThreadWork, min((j + 1) * oneThreadWork, maxWeight + 1));
            }

            /// notifies workers that there are jobs available
            queueCv.notify_all();
        }
    });


    /// creates the designated number of thread workers and adds them to the thread pool
    for (int i = 0; i < numOfWorkers; i++) {
        threadPool.emplace_back([&] {
            std::tuple<int, int, int> job;
            do {
                std::unique_lock<std::mutex> queueLock(queueMu);

                /// waits until the job queue is not empty
                queueCv.wait(queueLock, [&] { return !queue.empty(); });

                /// then takes an available job, removes it from the queue and releases the mutex
                job = queue.front();
                queue.pop_front();
                queueLock.unlock();


                if (std::get<0>(job) != numOfWeights) {
                    /// do the job
                    worker(job);

                    /// decrease the number of working threads
                    queueLock.lock();
                    currentlyWorking--;
                    queueLock.unlock();

                    /// notifies support thread
                    workingCv.notify_one();
                }
            } while (std::get<0>(job) != numOfWeights);
        });
    }

    /// waits for all the threads to finish
    for (int i = 0; i < threadPool.size(); i++) {
        threadPool[i].join();
    }
    supportThread.join();
}
