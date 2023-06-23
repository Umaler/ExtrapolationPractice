#include "LinearLSMFunc.hpp"
#include <stdexcept>

namespace LSM {

double LinearFunction::operator()(double x) const {
    return k * x + b;
}

void LinearFunction::findParameters(const std::vector<Point>& data) {
    if(data.size() == 0)
        throw std::runtime_error("No data");

    double Sxx = 0, Sx = 0, Sy = 0, Sxy = 0;
    for(const auto& i : data) {
        Sxx += i.x * i.x;
        Sx += i.x;
        Sy += i.y;
        Sxy += i.x * i.y;
    }

    double mainDet = data.size() * Sxx - Sx * Sx;
    if(mainDet == 0)
        throw std::runtime_error("Main determinant is 0");

    double n = data.size();

    k = (n * Sxy - Sx * Sy) / (n * Sxx - Sx * Sx);
    b = (Sy - k * Sx) / n;
}

}
