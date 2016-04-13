//
// Created by Gavin on 4/10/2016.
//

#include <sstream>
#include <iomanip>
#include "Food.h"

namespace Gaming {

    const char Food::FOOD_ID = 'F';

    Food::Food(const Game &g, const Position &p, double capacity) : Resource(g, p, capacity) {

    }

    Food::~Food() {

    }

    void Food::print(std::ostream &os) const {
        std::string str;
        //str += Simple::SIMPLE_ID;
        str = std::to_string(__id);

        //os << '[';
        std::stringstream ss;
        ss << Food::FOOD_ID;
        ss << str;
        for (int i = 0; i < (4 - str.length()); ++i)
            ss << ' ';
        std::getline(ss, str);
        //os << ss.rdbuf(); //<< ']';
        for (int i = 0; i < str.length(); ++i) {
            os << str[i];
        }
    }
}