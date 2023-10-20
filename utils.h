#ifndef PCC_SEMESTRAL_PROJECT_UTILS_H
#define PCC_SEMESTRAL_PROJECT_UTILS_H

#include <chrono>
#include <iostream>

template <typename TimePoint>
std::chrono::milliseconds to_ms(TimePoint tp) {
    return std::chrono::duration_cast<std::chrono::milliseconds>(tp);
}

void generateInput();

#endif //PCC_SEMESTRAL_PROJECT_UTILS_H
