#include <iostream>
#include <fstream>
#include "internal/methods.h"
#include <omp.h>
#include<string.h>
#include<chrono>


int main() {
    auto begin = std::chrono::high_resolution_clock::now();
    OmpSolve solve;
    solve.createFiles("testFile2.txt", 3, 400);
    double testX = solve.ompSolve("testFile2.txt", 400, 4);
    double test2X = solve.simpleSolve("testFile2.txt", 400);

    return 0;
}
