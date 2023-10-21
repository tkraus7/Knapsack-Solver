#ifndef PCC_SEMESTRAL_PROJECT_UTILS_H
#define PCC_SEMESTRAL_PROJECT_UTILS_H

#include <chrono>
#include <iostream>

template <typename TimePoint>
std::chrono::milliseconds to_ms(TimePoint tp) {
    return std::chrono::duration_cast<std::chrono::milliseconds>(tp);
}

/**
 * Generates file with input data for ./Knapsack based on values from the user.
 */
void generateInput();

#endif //PCC_SEMESTRAL_PROJECT_UTILS_H
