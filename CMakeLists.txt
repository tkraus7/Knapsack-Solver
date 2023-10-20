cmake_minimum_required(VERSION 3.23)
project(pcc_semestral_project)

set(CMAKE_CXX_STANDARD 17)

add_executable(KnapsackSolver main.cpp
        KnapsackSingle.cpp
        Knapsack.h
        KnapsackSingle.h
        Knapsack.cpp
        KnapsackParallel.cpp
        KnapsackParallel.h
        utils.cpp
        utils.h
)

set_target_properties(${pcc_semestral_project} PROPERTIES OUTPUT_NAME "KnapsackSolver")

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(KnapsackSolver Threads::Threads)
