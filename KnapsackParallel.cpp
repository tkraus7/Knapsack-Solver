#include <cmath>
#include <iostream>
#include "KnapsackParallel.h"

KnapsackParallel::KnapsackParallel(std::ifstream &in, int numOfThreads) :
        Knapsack(in),
        numOfThreads(numOfThreads),
        currentlyWorking(0) {}

//void KnapsackParallel::joinAll() {
//    for (int i = 0; i < threadPool.size(); i++) {
//        threadPool[i].join();
//    }
////    supportThread.join();
//}

void KnapsackParallel::worker(std::tuple<int, int, int> job) {
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

void KnapsackParallel::solveKnapsack() {
    for (int i = WEIGHTS[0][0]; i <= maxWeight; i++) {
        KNAPSACK[0][i] = WEIGHTS[0][1];
    }

    int numOfWorkers = (maxWeight / numOfThreads) >= 5 ? numOfThreads : 1;
    int oneThreadWork = std::round(maxWeight / numOfWorkers) + 1;

    supportThread = std::thread([&]() {
        for (int i = 1; i <= numOfWeights; i++) {
            std::unique_lock<std::mutex> queueLock(queueMu);
            workingCv.wait(queueLock, [&] { return currentlyWorking == 0; });
            for (int j = 0; j < numOfWorkers; j++) {
                currentlyWorking++;
//                std::cout << "adding " << i << " " << j * oneThreadWork << " "
//                          << std::min((j + 1) * oneThreadWork, maxWeight + 1) << std::endl;
                queue.push_back(std::tuple<int, int, int>(i, j * oneThreadWork,
                                                          std::min((j + 1) * oneThreadWork, maxWeight + 1)));
            }
            queueCv.notify_all();
        }
    });


    for (int i = 0; i < numOfWorkers; i++) {
        threadPool.push_back(std::thread([&]() {
            std::tuple<int, int, int> job;
            do {
                std::unique_lock<std::mutex> queueLock(queueMu);
                queueCv.wait(queueLock, [&]() { return !queue.empty(); });
                job = queue.front();
                queue.pop_front();
                queueLock.unlock();
                if (std::get<0>(job) != numOfWeights) {
                    worker(job);
                    currentlyWorking--;
                    workingCv.notify_one();
                }
            } while (std::get<0>(job) != numOfWeights);
        }));
    }

    for (int i = 0; i < threadPool.size(); i++) {
        threadPool[i].join();
    }
    supportThread.join();
}
