#include <iostream>
#include <fstream>
#include <math.h>
#include <iomanip>

/** заполняет файл значенями**/

int main() {
    srand(time(NULL));
    std::ofstream expFile;          //создаем поток для записи
    expFile.open("../files/testFile1.txt"); // открываем файл для записи

    if (expFile.is_open()) {
        for (int i = 1; i <= 100; i++) {
            expFile << double((i * exp(5.15))) << std::setprecision(2) << std::fixed << std::endl;
        }
    }
    expFile.close();
    std::cout << "File has been written!" << std::endl;
}