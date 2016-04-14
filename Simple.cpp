//
// Created by Gavin on 4/10/2016.
//

#include <sstream>
#include <string>
#include <iomanip>
#include "Simple.h"

namespace Gaming {

    const char Simple::SIMPLE_ID = 'S';

    Simple::Simple(const Game &g, const Position &p, double energy) : Agent(g, p, energy) {

    }

    Simple::~Simple() {

    }

    void Simple::print(std::ostream &os) const {
        std::string str;
        //str += Simple::SIMPLE_ID;
        str = std::to_string(__id);

        //os << '[';
        std::stringstream ss;
        ss << Simple::SIMPLE_ID;
        ss << str;
        /*for (int i = 0; i < (4 - str.length()); ++i)
            ss << ' ';*/
        std::getline(ss, str);
        //os << ss.rdbuf(); //<< ']';
        for (int i = 0; i < str.length(); ++i) {
            os << str[i];
        }
    }

    ActionType Simple::takeTurn(const Surroundings &s) const {
        std::vector<int> positions;
        //Check for Resource
        for (int i = 0; i < 9; ++i) {
            if (s.array[i] == PieceType::ADVANTAGE || s.array[i] == PieceType::FOOD)
                 positions.push_back(i);
        }
        if (positions.size() > 0) {
            std::cout << "Position Resource Options: " << positions.size() << std::endl;
            PositionRandomizer rand;
            Position pos = rand(positions);
            return (ActionType)(pos.y + (pos.x * 3));
        }
        //Check for Empty
        //if (positions.size() == 0) {
            for (int i = 0; i < 9; ++i) {
                if (s.array[i] == PieceType::EMPTY)
                    positions.push_back(i);
            }
        //}

        if (positions.size() > 0) {
            std::cout << "Position Empty Options: " << positions.size() << std::endl;
            PositionRandomizer rand();
            Position pos = rand(positions);
            std::cout << "Position Chosen: " << pos.y + (pos.x * 3) << std::endl;
            return (ActionType)(pos.y + (pos.x * 3));
        }

        return ActionType::STAY;
    }
}