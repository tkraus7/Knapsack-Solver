#include <random>
#include <fstream>
#include "utils.h"

double get_random_double() {
    static std::mt19937 mt{std::random_device{}()};
    static std::uniform_real_distribution<> dist(0, 1);
    return dist(mt);
}

double getRandom(double flo, double ceil) {
    return flo + ((ceil - flo) * get_random_double());
}

void generateInput() {
    int weight, numOfWeights;
    std::string filename;

    std::cout << "Enter total weight:";
    std::cin >> weight;
    std::cout << "Enter total number of weights:";
    std::cin >> numOfWeights;
    std::cout << "Enter output file name:";
    std::cin >> filename;

    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "ERROR: file error" << std::endl;
        return;
    }

    file << weight << " " << numOfWeights << "\n";
    int currWeight, currCost;
    for (int i = 0; i < numOfWeights; i++) {
        currWeight = ceil(getRandom(1, weight * 0.75));
        currCost = ceil(currWeight * getRandom(0.9, 2));
        file << currWeight << " " << currCost << "\n";
    }

    file.close();
}
