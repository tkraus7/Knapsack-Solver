cmake_minimum_required(VERSION 3.23)
project(pcc_semestral_project)

set(CMAKE_CXX_STANDARD 17)

add_executable(KnapsackSolver main.cpp
        knapsackSingle.cpp
        knapsack.h
        knapsackSingle.h)

set_target_properties(${pcc_semestral_project} PROPERTIES OUTPUT_NAME "KnapsackSolver")
