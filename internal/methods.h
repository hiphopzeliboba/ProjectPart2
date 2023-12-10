#include <string>
#include <math.h>

double solve(int i, std::string line){
    return log(std::stod(line)/i);
}