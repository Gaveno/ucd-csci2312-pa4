//
// Created by Gavin on 4/10/2016.
//

#include <sstream>
#include <iomanip>
#include "Strategic.h"

namespace Gaming {

    const char Strategic::STRATEGIC_ID = 'T';

    Strategic::Strategic(const Game &g, const Position &p, double energy, Strategy *s)
    : Agent(g, p, energy) {

    }

    Strategic::~Strategic() {

    }

    void Strategic::print(std::ostream &os) const {
        std::string str;
        //str += Simple::SIMPLE_ID;
        str = std::to_string(__id);

        //os << '[';
        std::stringstream ss;
        ss << Strategic::STRATEGIC_ID;
        ss << str;
        for (int i = 0; i < (4 - str.length()); ++i)
            ss << ' ';
        std::getline(ss, str);
        //os << ss.rdbuf(); //<< ']';
        for (int i = 0; i < str.length(); ++i) {
            os << str[i];
        }
    }

    ActionType Strategic::takeTurn(const Surroundings &s) const {
        //Check for Agent
        for (int i = 0; i < 9; ++i) {
            if (s.array[i] == PieceType::SIMPLE || s.array[i] == PieceType::STRATEGIC)
                return (ActionType)i;
        }
        //Check for Advantage
        for (int i = 0; i < 9; ++i) {
            if (s.array[i] == PieceType::ADVANTAGE)
                return (ActionType)i;
        }
        //Check for Food
        for (int i = 0; i < 9; ++i) {
            if (s.array[i] == PieceType::FOOD)
                return (ActionType)i;
        }
        //Check for Empty
        for (int i = 0; i < 9; ++i) {
            if (s.array[i] == PieceType::EMPTY)
                return (ActionType)i;
        }

        return ActionType::STAY;
    }
}