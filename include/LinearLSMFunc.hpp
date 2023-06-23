#pragma once

#include "LSMFunction.hpp"

namespace LSM {

class LinearFunction : public Function {
public:

    virtual double operator()(double x) const override;
    virtual void findParameters(const std::vector<Point>& data) override;

    virtual void printCoef(std::ostream& output) override;

protected:
    //y = kx + b
    double k = 0;
    double b = 0;

};

}
