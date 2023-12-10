#include <iostream>
#include <fstream>
#include "internal/methods.h"
#include <omp.h>
#include<string>



int main() {
    int j=1;
    std::ifstream file("../files/testFile1.txt");
    if (!file.is_open()) {
        std::cerr << "Error opening file" << std::endl;
        return 1;
    }
#pragma omp parallel num_threads(4) shared(j)
#pragma omp for
    for(int i =1; i<=100; ++i){
        std::string line;
#pragma omp critical
        std::getline(file, line);
#pragma omp critical
        std::cout<<"i= "<<j<<" line= "<<line<<" res= "<< solve(j,line)<<" thread= "<<omp_get_thread_num()<<std::endl;
        ++j;
    }

    file.close();
    return 0;
}
