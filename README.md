# Knapsack Solver

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

Solver for 0-1 Knapsack problem.

### PCC Assignment

Implement a program for solving 0-1 Knapsack problems. Also implement a version of the program running on multiple threads. Then compare both versions.

## Problem description

Given a set of weights, each with a weight and a cost, determine which weights to include in the collection (Knapsack) so that the total weight is less than or equal to a given limit and the total cost is as large as possible.

We say that the problem is 0-1 because each weight is either not in the Knapsack (0) or it is (1).

[Knapsack Problem on Wikipedia](https://en.wikipedia.org/wiki/Knapsack_problem)

## Installation 

Clone the repository and use `CMake` to build the project using the included `CMakeList.txt`.

## Usage

* `-f [filename]`, `--file [filename]` to specify input data file.
* `-v`, `--verbose` to print the verbose version of the solution.
* `-g`, `--generate` to generate a input data file.
* `-p [number]`, `--parallel [number]` to run the multi-threaded version of this program using the specified number of threads.

Example: `./KnapsackSolver -f ../data/pub03.in -v -p 5`

## Implementation

A dynamic programming approach is used to solve the problem. Given the maximum Knapsack weight $W$ and $N$ weights, each with it's own weight $w_i$ and cost $c_i$, create a 
table $M$ of size $N(W+1)$, where $M[i, w]$ is the maximum cost that
can be achieved with Knapsack weight less than or equal to $w$ using only first $i$ items. 

We can then fill up $M$ recursively as follows:

$$ 
\begin{align} 
M[1,w] &= \text{if}\ w_i \leq w\ \text{then}\ c_i\ \text{else}\ 0\\ 
M[i,w] &= M[i-1,\ w]\ \text{if}\ w_i > w \\
M[i,w] &= max(m[i-1,\ w],\ m[i-1,\ w-w_i]\ +\ c_i)\ \text{if}\ w_i \leq w. 
\end{align}
$$

The largest possible Knapsack cost can then be found in $M[N,W]$. In order to found out the weights used, backtrack the solution as follows:

```
weights_used = [];

i = N, j = W;
for i in N..0 do:
    current = M[i, j];
    if (M[i - 1][j] != current) then:
        j -= Weights[i];
        weights_used.add(Weights[i], Costs[i])

return weights_used;
```
  
### Multi-threaded implementation

The multi-threded implementation is based on the fact that every row in $M$ (apart from the first one) is only dependant on the row right above it. 
Each row of the table is therefore divided equally amongst all available threads. Once the're all finished, work on a next row is started.

## Input file format

First row contains two integers: the maximum Knapsack capacity $(W)$ and the total number of weights $(N)$ respectively. After that comes $N$ lines,
each with two integers signifying the weight and cost of the specific weight. 

You can find examples in `/data`.

## Speed measurement

The speed measurement was done against code in commit `65c6a90` on a 6 core i7-8700 CPU @ 3.20GHz. The run times are shown in miliseconds.
<div align="center">
  
|Knapsack capacity  | number of weights | ST | MT(5) | MT(15) |
|:-----------------:|:-----------------:|-----:|-----:|-----:|
|200	|50|	0|	5|	9|
|500|50|	0|	6	|9|
|1000|	50|	0|	7|	9|
|5000	|200|	0|	20|	36|
|10000|	500|	3|	52|	102|
|50000|	500|	17|	63|	133|
|100000|	500|	35|	73|	137|
|500000|	500|	183|	151|	226|
|1000000|	500|	384|	270|	380|
|5000000|	500|	2079|	1419|	1487|
|10000000|	300|	2510|	1641|	1700|
|100000000|	30|	2381|	1606|	1589|

</div>

Since the multi-threading implementation only divides each row amongst available threads, it can only overcome the threading overhead when the rows are satisfyingly long.
On rows that are < ~500'000 numbers long it's better to use the single-thread version.



