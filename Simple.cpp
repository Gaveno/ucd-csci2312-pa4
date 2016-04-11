//
// Created by Gavin on 4/10/2016.
//

#include "Simple.h"

namespace Gaming {

    const char Simple::SIMPLE_ID = 'S';

    Simple::Simple(const Game &g, const Position &p, double energy) : Agent(g, p, energy) {

    }

    Simple::~Simple() {

    }

    void Simple::print(std::ostream &os) const {

    }

    ActionType Simple::takeTurn(const Surroundings &s) const {

    }
}