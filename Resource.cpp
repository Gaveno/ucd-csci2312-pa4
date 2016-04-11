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

    }

    void Resource::age() {

    }

    ActionType Resource::takeTurn(const Surroundings &s) const {

    }

    // note: these won't be called while resources don't move
    Piece &Resource::operator*(Piece &other) {

    }

    Piece &Resource::interact(Agent *) {

    }

    Piece &Resource::interact(Resource *) { // note: no interaction between resources

    }
}