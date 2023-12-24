#include <string>
#include <iostream>
#include <chrono>
#include <math.h>
#include <vector>
#include <fstream>

class OmpSolve {
    std::string filePath = "./files/";
    double eps = 0.2;
public:
    /**
     * создает файл с определенным кол-вом строк, и заполняет строки согласно условию задачи
     *
     * @param fileName - название файла с значениями
     * @param lineNum - количество строк в файле
     * @param x - искомое значение Х
     * **/
    void createFiles(std::string fileName, float x, int lineNum) {

        std::ofstream testFile; //создаем поток для записи
        testFile.open(filePath + fileName); // открываем файл для записи
        if (testFile.is_open()) { // если файл открыт для записи, то заполняем стрки по формуле
            for (int i = 1; i <= lineNum; i++) {
                testFile << double(i * (exp(x) + 0.001 + rand() % 1)) << "\n";
            }
        }
        testFile.close();
        std::cout << "File has been written!" << std::endl;

    };

    /**
     * решение с помощью ОМП и методом МНК
     *
     * @param fileName - название файла с значениями
     * @param lineNum - количество строк в файле
     * @param threadsNum - количество потоков
     * **/
    double ompSolve(std::string fileName, int lineNum, int threadsNum) {
        auto begin = std::chrono::high_resolution_clock::now();

        double ySum, yxSum = 0; // переменные для суммирования значений У и У*Х, где у - значение строки, х - номер строки
        std::vector<double> yArray{0};
        std::string line;

        std::ifstream testFile;          //создаем поток для записи
        testFile.open(filePath + fileName); // открываем файл для записи
        if (!testFile.is_open()) {
            std::cerr << "Error opening text file" << std::endl;
        }

        //заполняем вектор значениями из файла
        for (int i = 1; i <= lineNum; i++) {
            std::getline(testFile, line);
            yArray.push_back(stod(line));
        }

        // считаем сумму значений из файла
#pragma omp parallel for reduction(+:ySum) num_threads(threadsNum)
        for (int i = 0; i <= lineNum; i++) {
            ySum += yArray[i];
        }

        //считаем сумму значений У*Х, где у-значение строки, х - сответвенное значение i (номер строки)
#pragma omp parallel for reduction(+:yxSum) num_threads(threadsNum)
        for (int i = 0; i <= lineNum; i++) {
            yxSum += (yArray[i] * i);
        }

        double yAve = ySum / lineNum; // среднее значение У
        double yxAve = yxSum / lineNum; // среднее значение у*х
        double xAve = ((1 + lineNum) / 2 * lineNum) / lineNum; // среднее значение х
        double xxAve = (lineNum * (lineNum + 1) * (2 * lineNum + 1) / 6) / lineNum; // среднее значение х*х
        double B2 = (yxAve - xAve * yAve) / (xxAve - xAve * xAve); // расчет коэффициента В2
        std::cout << "log(exp(x) = " << log(B2) << std::endl;
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> duration = end - begin;
        std::cout << "Time solving - " << duration.count()<<std::endl;
        return log(B2);
    }

    /**
     * линейное решение без использования ОМП
     *
     * @param fileName - название файла с значениями
     * @param lineNum - количество строк в файле
     * **/
    double simpleSolve(std::string fileName, int lineNum) {
        auto begin = std::chrono::high_resolution_clock::now();
        double ySum, yxSum = 0;
        std::vector<double> yArray{0};
        std::string line;
        std::ifstream testFile;          //создаем поток для записи
        testFile.open(filePath + fileName); // открываем файл для записи
        if (!testFile.is_open()) {
            std::cerr << "Error opening text file" << std::endl;
        }

        for (int i = 1; i <= lineNum; i++) {
            std::getline(testFile, line);
            yArray.push_back(stod(line));
        }
        for (int i = 0; i <= lineNum; i++) {
            ySum += yArray[i];
            yxSum += (yArray[i] * i);
        }
        double yAve = ySum / lineNum;
        double yxAve = yxSum / lineNum;
        double xAve = ((1 + lineNum) / 2 * lineNum) / lineNum;
        double xxAve = (lineNum * (lineNum + 1) * (2 * lineNum + 1) / 6) / lineNum;
        double B2 = (yxAve - xAve * yAve) / (xxAve - xAve * xAve);
        std::cout << "log(exp(x) = " << log(B2) << std::endl;
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> duration = end - begin;
        std::cout << "Time solving - " << duration.count()<<std::endl;
        return log(B2);
    }


};

