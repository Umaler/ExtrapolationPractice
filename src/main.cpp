#include <iostream>
#include <vector>
#include <fstream>
#include "LinearLSMFunc.hpp"
#include "Loaders.hpp"

int main() {
    auto data = LSM::loadStringFromCSV(std::cin);
    LSM::LinearFunction func;
    func.findParameters(data);
    std::cout << func(1);
}
