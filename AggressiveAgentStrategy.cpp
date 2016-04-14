//
// Created by Gavin on 4/10/2016.
//

#include "Game.h"
#include "AggressiveAgentStrategy.h"

namespace Gaming {

    const double AggressiveAgentStrategy::DEFAULT_AGGRESSION_THRESHOLD = Game::STARTING_AGENT_ENERGY * 0.75;

    AggressiveAgentStrategy::AggressiveAgentStrategy(double agentEnergy) {

    }

    AggressiveAgentStrategy::~AggressiveAgentStrategy() {

    }

    ActionType AggressiveAgentStrategy::operator()(const Surroundings &s) const {
        return ActionType::STAY;
    }

}