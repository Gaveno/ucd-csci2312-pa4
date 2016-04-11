//
// Created by Gavin on 4/10/2016.
//

#include "Advantage.h"

namespace Gaming {

    const char Advantage::ADVANTAGE_ID = 'D';
    const double Advantage::ADVANTAGE_MULT_FACTOR = 2.0;

    Advantage::Advantage(const Game &g, const Position &p, double capacity) : Resource(g, p, capacity) {

    }

    Advantage::~Advantage() {

    }

    void Advantage::print(std::ostream &os) const {

    }

    double Advantage::getCapacity() const {
        return __capacity * ADVANTAGE_MULT_FACTOR;
    }

    double Advantage::consume() {

    }

}