#!/bin/bash

FILES="./data/*"
IFS=' '

printf '%s\n' "knapscak capacity,number of weights,ST,MT(5),MT(15)"
for f in $FILES
do
    line=$(head -n 1 "$f")
    read -r -a strarr <<< "$line"
    capacity=${strarr[0]}
    weights=${strarr[1]}

    resST=$(./cmake-build-debug/KnapsackSolver -f "$f")
    resMT5=$(./cmake-build-debug/KnapsackSolver -f "$f" -p 5)
    resMT15=$(./cmake-build-debug/KnapsackSolver -f "$f" -p 15)

    timeST=$(echo "$resST" | tail -n 1)
    timeMT5=$(echo "$resMT5" | tail -n 1)
    timeMT15=$(echo "$resMT15" | tail -n 1)

    printf '%d,%d,%d,%d,%d\n' "$capacity" "$weights" "$timeST" "$timeMT5" "$timeMT15"
    
done
