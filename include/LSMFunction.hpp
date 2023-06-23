#pragma once

#include <vector>
#include <ostream>

namespace LSM {

struct Point {
    double x;
    double y;
};

class Function {
public:

    Function() = default;

    virtual double operator()(double x) const = 0;
    virtual void findParameters(const std::vector<Point>& data) = 0;

    virtual void printCoef(std::ostream& output) = 0;

    virtual ~Function() = default;

};

}
