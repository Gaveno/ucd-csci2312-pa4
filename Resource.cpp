//
// Created by Gavin on 4/10/2016.
//

#include "Resource.h"

namespace Gaming {

    const double Resource::RESOURCE_SPOIL_FACTOR = 1.2;

    Resource::Resource(const Game &g, const Position &p, double capacity) : Piece(g, p) {

    }

    Resource::~Resource() {

    }

    double Resource::consume() {
        double ret = __capacity;
        __capacity = 0;
        return ret;
    }

    void Resource::age() {

    }

    ActionType Resource::takeTurn(const Surroundings &s) const {
        return ActionType::STAY;
    }

    // note: these won't be called while resources don't move
    Piece &Resource::operator*(Piece &other) {

    }

    Piece &Resource::interact(Agent *) {
        return *this;
    }

    Piece &Resource::interact(Resource *) { // note: no interaction between resources
        return *this;
    }
}