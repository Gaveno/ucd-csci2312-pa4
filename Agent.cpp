//
// Created by Gavin on 4/10/2016.
//

#include "Agent.h"
#include "Advantage.h"
#include "Food.h"

namespace Gaming {

    const double Agent::AGENT_FATIGUE_RATE = 0.3;

    Agent::Agent(const Game &g, const Position &p, double energy) : Piece(g, p) {

    }

    Agent::~Agent() {

    }

    void Agent::age() {
        __energy -= AGENT_FATIGUE_RATE;
    }

    Piece &Agent::operator*(Piece &other) {

    }

    Piece &Agent::interact(Agent *other) {
        if (__energy == other->__energy) {
            finish();
            other->finish();
        }
        else {
            if (__energy > other->__energy) {
                __energy -= other->__energy;
                other->finish();
            }
            else {
                other->__energy -= __energy;
                finish();
            }
        }
        return *this;
    }

    Piece &Agent::interact(Resource *other) {
        Advantage *adv = dynamic_cast<Advantage*>(other);
        if (adv) {
            __energy += adv->getCapacity();
        }
        else {
            // Must be food
            __energy += other->getCapacity();
        }
        return *this;
    }

}