//
// Created by Gavin on 4/10/2016.
//

#include <sstream>
#include <string>
#include <iomanip>
#include <random>
#include <chrono>
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
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::default_random_engine rnd(seed);

        for (int i = 0; i < 9; ++i) {
            if (s.array[i] == PieceType::ADVANTAGE || s.array[i] == PieceType::FOOD)
                 positions.push_back(i);
        }
        if (positions.size() > 0) {
            if (positions.size() == 1) return (ActionType)positions[0];
            int posIndex = positions[rnd() % positions.size()];
            return (ActionType)(posIndex);
        }
        //Check for Empty
        //if (positions.size() == 0) {
            for (int i = 0; i < 9; ++i) {
                if (s.array[i] == PieceType::EMPTY) {
                    positions.push_back(i);
                    std::cout << "Available position: " << i << std::endl;
                }
            }
        //}

        if (positions.size() > 0) {
            if (positions.size() == 1) return (ActionType)positions[0];
            int posIndex = positions[rnd() % positions.size()];
            std::cout << "Chosen Action: " << posIndex << std::endl;
            return (ActionType)(posIndex);
        }

        return ActionType::STAY;
    }
}