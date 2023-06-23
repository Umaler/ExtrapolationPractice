#include "Loaders.hpp"
#include <sstream>

namespace LSM {

std::vector<LSM::Point> loadStringFromCSV(std::istream& input) {
    std::vector<LSM::Point> result;

    size_t i = 0;
    std::stringstream str;
    while(!input.eof()) {
        char ch;
        input.get(ch);
        if(ch == ',' || ch == ';' || ch == '\n') {
            result.push_back({static_cast<double>(i), 0});
            str >> result.back().y;
            str.clear();
            i++;
            if(ch == '\n')
                break;
            else
                continue;
        }

        str << ch;
    }

    return result;
}

std::vector<std::vector<LSM::Point>> loadSetFromCSV(std::istream& input) {
    std::vector<std::vector<LSM::Point>> result;
    while(!input.eof()) {
        result.emplace_back(std::move(loadStringFromCSV(input)));
    }
    return result;
}

}
