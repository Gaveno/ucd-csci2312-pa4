//
// Created by Gavin on 4/10/2016.
//

#include "Strategic.h"

namespace Gaming {

    const char Strategic::STRATEGIC_ID = 'T';

    Strategic::Strategic(const Game &g, const Position &p, double energy, Strategy *s)
    : Agent(g, p, energy) {

    }

    Strategic::~Strategic() {

    }

    void Strategic::print(std::ostream &os) const {

    }

    ActionType Strategic::takeTurn(const Surroundings &s) const {

    }
}