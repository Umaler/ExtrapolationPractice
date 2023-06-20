#pragma once

#include "LSMFunction.hpp"

namespace LSM {

class LinearFunction : public Function {
public:

    virtual double operator()(double x) const;
    virtual void findParameters(const std::vector<Point>& data);

protected:
    //y = kx + b
    double k = 0;
    double b = 0;

};

}
