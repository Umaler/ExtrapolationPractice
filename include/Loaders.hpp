#pragma once

#include <vector>
#include <istream>
#include "LSMFunction.hpp"

namespace LSM {

std::vector<LSM::Point> loadStringFromCSV(std::istream& input);

}
