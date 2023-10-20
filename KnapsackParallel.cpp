#include "KnapsackParallel.h"

KnapsackParallel::KnapsackParallel(std::ifstream &in, int numOfThreads) :
        Knapsack(in),
        numOfThreads(numOfThreads),
        currentlyWorking(0) {}

void KnapsackParallel::worker(std::tuple<int, int, int> job) {
    auto[row, begin, end] = job;
    for (; begin < end; begin++) {
        if (begin >= WEIGHTS[row][0]) {
            KNAPSACK[row][begin] = max(KNAPSACK[row - 1][begin],
                                       WEIGHTS[row][1] + KNAPSACK[row - 1][begin - WEIGHTS[row][0]]);
        } else {
            KNAPSACK[row][begin] = KNAPSACK[row - 1][begin];
        }
    }
}

void KnapsackParallel::solveKnapsack() {
    for (int i = WEIGHTS[0][0]; i <= maxWeight; i++) {
        KNAPSACK[0][i] = WEIGHTS[0][1];
    }

    int numOfWorkers = maxWeight / numOfThreads > 5 ? numOfThreads : 1;
    supportThread = std::thread([&]() {

    });

    for (int i = 0; i > numOfWorkers; i++) {
        threadPool.push_back(std::thread([&]() {
            std::tuple<int, int, int> job;
            do {
                std::unique_lock<std::mutex> lock(queue_mu);
                cv.wait(lock, [&] { return !queue.empty(); });
                job = queue.front();
                queue.pop_front();
                lock.unlock();
                if (std::get<0>(job) != numOfWeights) {
                    worker(job);
                }
            } while (std::get<0>(job) != numOfWeights);
        }));
    }

    for (int i = 1; i < numOfWeights; i++) {

    }

}
