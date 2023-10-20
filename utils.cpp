#include <random>
#include "utils.h"

double get_random_double() {
    static std::mt19937 mt{std::random_device{}()};
    static std::uniform_real_distribution<> dist(-1000, 1000);
    return dist(mt);
}

void generateInput() {
    int weight, numOfWeights;
    std::string filename;

    std::cout << "Enter total weight: ";
    std::cin >> weight;
    std::cout << "Enter total number of weights: ";
    std::cin >> numOfWeights;
    std::cout << "Enter output file name: ";
    std::cin >> filename;


}
