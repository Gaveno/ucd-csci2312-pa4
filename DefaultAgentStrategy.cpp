//
// Created by Gavin on 4/10/2016.
//

#include "DefaultAgentStrategy.h"

namespace Gaming {

    DefaultAgentStrategy::DefaultAgentStrategy() {

    }

    DefaultAgentStrategy::~DefaultAgentStrategy() {

    }

    ActionType DefaultAgentStrategy::operator()(const Surroundings &s) const {
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
        //Check for Agent
        for (int i = 0; i < 9; ++i) {
            if (s.array[i] == PieceType::SIMPLE)
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