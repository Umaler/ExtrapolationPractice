#include <iostream>
#include "LinearLSMFunc.hpp"

int main() {
    std::vector<LSM::Point> data {{1.0, 2.0}, {1.1, 0.0}, {0.0, 0.0}};
    LSM::LinearFunction func;
    func.findParameters(data);
    std::cout << func(1.0) << std::endl;
}
