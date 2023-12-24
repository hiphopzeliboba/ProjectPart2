#include "../internal/methods.h"
#include <gtest/gtest.h>
#include <fstream>
#include <string.h>
#include <vector>
#include <iostream>
#include<chrono>

class CompTest : public ::testing::Test {
protected:
    std::string filePath = "./files/";
    double eps= 0.2;
    OmpSolve ompSolve;
    void SetUp() {

    }

    void SetDown() {
    }

};
TEST_F(CompTest, test0) {
    ompSolve.createFiles("testFile2.txt", 3, 200);
    double testX = ompSolve.simpleSolve("testFile2.txt", 200);
    EXPECT_TRUE(3-eps<testX<=3+eps);
}

TEST_F(CompTest, test1) {
    ompSolve.createFiles("testFile2.txt", 3, 200);
    double testX = ompSolve.ompSolve("testFile2.txt", 200, 4);
    EXPECT_TRUE(3-eps<testX<=3+eps);
}
TEST_F(CompTest, test2) {
    ompSolve.createFiles("testFile2.txt", 3, 200);
    double testX = ompSolve.ompSolve("testFile2.txt", 200, 2);
    EXPECT_TRUE(3-eps<testX<=3+eps);
}

TEST_F(CompTest, test3) {
    ompSolve.createFiles("testFile3.txt", 3.3, 100);
    double testX = ompSolve.ompSolve("testFile3.txt", 100, 6);
    EXPECT_TRUE(3.3-eps<testX<=3.3+eps);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
