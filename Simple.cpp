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
        //std::cout << "---- Simple::takeTurn -----" << std::endl;

        std::vector<int> positions;
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::default_random_engine rnd(seed);

        for (int i = 0; i < 9; ++i) {
            //std::cout << "Surr of " << __id << ": i: " << i << ": " << s.array[i] << std::endl;
            if (s.array[i] == PieceType::ADVANTAGE || s.array[i] == PieceType::FOOD) {
                //std::cout << "Pushing advantage" << std::endl;
                positions.push_back(i);
                //std::cout << "size of positions: " << positions.size() << std::endl;
            }
        }
        //Check for Empty
        if (positions.size() == 0) {
            for (int i = 0; i < 9; ++i) {
                //std::cout << "Surrounding[i]: " << s.array[i] << std::endl;
                if (s.array[i] == PieceType::EMPTY) {
                    positions.push_back(i);
                    //std::cout << "Available position: " << i << std::endl;
                }
            }
        }

        if (positions.size() > 0) {
            int posIndex = positions[rnd() % positions.size()];
            if (positions.size() == 1) posIndex = positions[0];

            //std::cout << "Chosen Position: " << posIndex << std::endl;
            ActionType ac;
            switch (posIndex) {
                case 0: ac = NW; break;
                case 1: ac = N; break;
                case 2: ac = NE; break;
                case 3: ac = W; break;
                case 4: ac = STAY; break;
                case 5: ac = E; break;
                case 6: ac = SW; break;
                case 7: ac = S; break;
                case 8: ac = SE; break;
                default: ac = STAY;
            }
            //std::cout << "Chosen Action: " << ac << std::endl;
            return (ac);
        }

        return ActionType::STAY;
    }
}