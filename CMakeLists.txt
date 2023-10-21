cmake_minimum_required(VERSION 3.23)
project(pcc_semestral_project)

set(CMAKE_CXX_STANDARD 17)

add_executable(KnapsackSolver src/main.cpp
        src/knapsackSingle/KnapsackSingle.cpp
        src/knapsack/Knapsack.h
        src/knapsackSingle/KnapsackSingle.h
        src/knapsack/Knapsack.cpp
        src/knapsackParallel/KnapsackParallel.cpp
        src/knapsackParallel/KnapsackParallel.h
        src/utils/utils.cpp
        src/utils/utils.h
)

set_target_properties(${pcc_semestral_project} PROPERTIES OUTPUT_NAME "KnapsackSolver")

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(KnapsackSolver Threads::Threads)
