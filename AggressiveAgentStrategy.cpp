//
// Created by Gavin on 4/10/2016.
//

#include "Game.h"
#include "AggressiveAgentStrategy.h"

namespace Gaming {

    const double AggressiveAgentStrategy::DEFAULT_AGGRESSION_THRESHOLD = Game::STARTING_AGENT_ENERGY * 0.75;

    AggressiveAgentStrategy::AggressiveAgentStrategy(double agentEnergy) {
        __agentEnergy = agentEnergy;
    }

    AggressiveAgentStrategy::~AggressiveAgentStrategy() {

    }

    ActionType AggressiveAgentStrategy::operator()(const Surroundings &s) const {
        //Check for Agent
        for (int i = 0; i < 9; ++i) {
            if (__agentEnergy > DEFAULT_AGGRESSION_THRESHOLD &&
                (s.array[i] == PieceType::SIMPLE || s.array[i] == PieceType::STRATEGIC))
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