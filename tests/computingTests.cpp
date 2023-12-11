#include "../internal/methods.h"
#include <gtest/gtest.h>
#include <fstream>
#include <string.h>
#include <iostream>
#include<chrono>

class CompTest : public ::testing::Test {
protected:
    std::string filePath = "./files/";

    void SetUp() {
    }

    void SetDown() {
    }

/**
 * @param fileName - название файла с значениями
 * @param lineNum - количество строк в файле
 * @param x - искомое значение Х
 * **/
    void createFiles(std::string fileName, float x, int lineNum) {
        std::ofstream testFile;          //создаем поток для записи
        testFile.open(filePath + fileName); // открываем файл для записи

        if (testFile.is_open()) {
            for (int i = 1; i <= lineNum; i++) {
                testFile << double((i * exp(x))) << std::setprecision(2) << std::fixed << std::endl;
            }
        }
        testFile.close();
        std::cout << "File has been written!" << std::endl;

    };
/**
 * @param fileName - название файла с значениями
 * @param lineNum - количество строк в файле
 * @param threadsNum - количество потоков
 * **/
    double ompSolve(std::string fileName, int lineNum, int threadsNum) {
        auto begin = std::chrono::high_resolution_clock::now();
        double expoSum = 0;
        //int j = 1;
        std::ifstream testFile;          //создаем поток для записи
        testFile.open(filePath + fileName); // открываем файл для записи

        if (testFile.is_open()) {
#pragma omp parallel num_threads(threadsNum) //shared(i)
#pragma omp for
            for (int i = 1; i <= lineNum; ++i) {
                std::string line;
#pragma omp critical
                std::getline(testFile, line);

                expoSum+= solve(i, line); //j
                //++j;
        }

    }
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> duration = end -begin;
        std::cout<<duration.count();
        return expoSum/lineNum;
}
double simpleSolve(std::string fileName, int lineNum){
    auto begin = std::chrono::high_resolution_clock::now();
    double expoSum = 0;
    std::string line;
    std::ifstream testFile;          //создаем поток для записи
    testFile.open(filePath + fileName); // открываем файл для записи
    if (testFile.is_open()) {
        for (int i = 1; i <= lineNum; ++i) {
            std::getline(testFile, line);
            expoSum+= solve(i, line);
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> duration = end -begin;
    std::cout<<duration.count();
    return expoSum/lineNum;
    }

};
TEST_F(CompTest, test0) {
    createFiles("testFile2.txt", 3, 200);
    //auto begin = std::chrono::high_resolution_clock::now();
    double testX = simpleSolve("testFile2.txt", 200);
    //auto end = std::chrono::high_resolution_clock::now();
    //std::chrono::duration<float> duration = end -begin;
    //std::cout<<duration.count();
    EXPECT_EQ(round(testX*10)/10, 3);
}

TEST_F(CompTest, test1) {
    createFiles("testFile2.txt", 3, 200);
    //auto begin = std::chrono::high_resolution_clock::now();
    double testX = ompSolve("testFile2.txt", 200, 4);
    //auto end = std::chrono::high_resolution_clock::now();
    //std::chrono::duration<float> duration = end -begin;
    //std::cout<<duration.count();
    EXPECT_EQ(round(testX*10)/10, 3);
}
TEST_F(CompTest, test2) {
    createFiles("testFile2.txt", 3, 200);
    //auto begin = std::chrono::high_resolution_clock::now();
    double testX = ompSolve("testFile2.txt", 200, 2);
    //auto end = std::chrono::high_resolution_clock::now();
    //std::chrono::duration<float> duration = end - begin;
    //std::cout << duration.count();
    EXPECT_EQ(round(testX * 10) / 10, 3);
}

TEST_F(CompTest, test3) {
    createFiles("testFile3.txt", 3.3, 100);
   // auto begin = std::chrono::high_resolution_clock::now();
    double testX = ompSolve("testFile3.txt", 100, 6);
    //auto end = std::chrono::high_resolution_clock::now();
    //std::chrono::duration<float> duration = end -begin;
    //std::cout<<duration.count();
    EXPECT_EQ(round(testX*10)/10, 3.3);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
