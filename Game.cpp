//
// Created by Gavin on 4/10/2016.
//

#include "Game.h"
#include "Simple.h"
#include "Strategic.h"
#include "Food.h"
#include "Advantage.h"

namespace Gaming {

    const unsigned int Game::NUM_INIT_AGENT_FACTOR = 4;
    const unsigned int Game::NUM_INIT_RESOURCE_FACTOR = 2;
    const unsigned Game::MIN_WIDTH = 3;
    const unsigned Game::MIN_HEIGHT = 3;
    const double Game::STARTING_AGENT_ENERGY = 20;
    const double Game::STARTING_RESOURCE_CAPACITY = 10;

    PositionRandomizer Game::__posRandomizer = PositionRandomizer();

    // PRIVATE
    void Game::populate() { // populate the grid (used in automatic random initialization of a Game)
        std::default_random_engine gen;
        std::uniform_int_distribution<int> d(0, __width * __height);

        int numStrategic = (int)((__width * __height) / NUM_INIT_AGENT_FACTOR / 2.0);
        int numSimple = numStrategic;

        while (numStrategic > 0) {
            int i = d(gen);
            if (__grid[i] == nullptr) {
                Position pos(i / __width, i % __width);
                __grid[i] = new Strategic(*this, pos, STARTING_AGENT_ENERGY);
                numStrategic--;
            }
        }

        while (numSimple > 0) {
            int i = d(gen);
            if (__grid[i] == nullptr) {
                Position pos(i / __width, i % __width);
                __grid[i] = new Simple(*this, pos, STARTING_AGENT_ENERGY);
                numSimple--;
            }
        }

        int numFood = (__width * __height) / NUM_INIT_RESOURCE_FACTOR / 2;
        int numAdv = numFood;

        while (numFood > 0) {
            int i = d(gen);
            if (__grid[i] == nullptr) {
                Position pos(i / __width, i % __width);
                __grid[i] = new Food(*this, pos, STARTING_RESOURCE_CAPACITY);
                numFood--;
            }
        }

        while (numAdv > 0) {
            int i = d(gen);
            if (__grid[i] == nullptr) {
                Position pos(i / __width, i % __width);
                __grid[i] = new Advantage(*this, pos, STARTING_RESOURCE_CAPACITY);
                numAdv--;
            }
        }
    }

    //PUBLIC
    //Constructors / Destructor
    Game::Game() : __width(3), __height(3) {
        for (unsigned i = 0; i < (__width * __height); ++i) {
            __grid.push_back(nullptr);
        }
    }

    Game::Game(unsigned width, unsigned height, bool manual) : __width(width), __height(height) { // note: manual population by default
        if (width < MIN_WIDTH || height < MIN_HEIGHT) {
            throw InsufficientDimensionsEx(MIN_WIDTH, MIN_HEIGHT, width, height);
        }

        for (unsigned i = 0; i < (__width * __height); ++i) {
            __grid.push_back(nullptr);
        }

        if (!manual) {
            populate();
        }
    }

    Game::Game(const Game &another) {

    }

    Game::~Game() {
        for (auto it = __grid.begin(); it != __grid.end(); ++it) {
            if (*it != nullptr) {
                delete *it;
            }
        }
    }

    // Accessors
    unsigned int Game::getNumPieces() const {
        unsigned int numPieces = 0;
        for (auto it = __grid.begin(); it != __grid.end(); ++it) {
            if (*it != nullptr)
                numPieces++;
        }

        return numPieces;
    }

    unsigned int Game::getNumAgents() const {
        unsigned int numAgents = 0;

        for (auto it = __grid.begin(); it != __grid.end(); ++it) {
            Agent *simple = dynamic_cast<Agent*>(*it);
            if (simple) numAgents ++;
        }

        return numAgents;
    }

    unsigned int Game::getNumSimple() const {
        unsigned int numAgents = 0;

        for (auto it = __grid.begin(); it != __grid.end(); ++it) {
            Simple *simple = dynamic_cast<Simple*>(*it);
            if (simple) numAgents ++;
        }

        return numAgents;
    }

    unsigned int Game::getNumStrategic() const {
        unsigned int numAgents = 0;

        for (auto it = __grid.begin(); it != __grid.end(); ++it) {
            Strategic *simple = dynamic_cast<Strategic*>(*it);
            if (simple) numAgents ++;
        }

        return numAgents;
    }

    unsigned int Game::getNumResources() const {
        unsigned int numAgents = 0;

        for (auto it = __grid.begin(); it != __grid.end(); ++it) {
            Resource *simple = dynamic_cast<Resource*>(*it);
            if (simple) numAgents ++;
        }

        return numAgents;
    }

    const Piece *Game::getPiece(unsigned int x, unsigned int y) const {
        if (x >= __width || y >= __height) throw OutOfBoundsEx(__width, __height, x, y);
        return __grid[x + (y * __width)];
    }

    // grid population methods
    void Game::addSimple(const Position &position) {
        if (__grid[position.x + (position.y * __width)]) throw PositionNonemptyEx(position.x, position.y);
        if (position.x >= __width || position.y >= __height) throw OutOfBoundsEx(__width, __height, position.x, position.y);

        __grid[position.x + (position.y * __width)] = new Simple(*this, position, STARTING_AGENT_ENERGY);
    }

    void Game::addSimple(const Position &position, double energy) { // used for testing only
        if (__grid[position.x + (position.y * __width)]) throw PositionNonemptyEx(position.x, position.y);
        if (position.x >= __width || position.y >= __height) throw OutOfBoundsEx(__width, __height, position.x, position.y);

        __grid[position.x + (position.y * __width)] = new Simple(*this, position, energy);
    }

    void Game::addSimple(unsigned x, unsigned y) {
        if (__grid[x + (y * __width)]) throw PositionNonemptyEx(x, y);
        if (x >= __width || y >= __height) throw OutOfBoundsEx(__width, __height, x, y);

        __grid[x + (y * __width)] = new Simple(*this, Position(x, y), STARTING_AGENT_ENERGY);
    }

    void Game::addSimple(unsigned x, unsigned y, double energy) {
        if (__grid[x + (y * __width)]) throw PositionNonemptyEx(x, y);
        if (x >= __width || y >= __height) throw OutOfBoundsEx(__width, __height, x, y);

        __grid[x + (y * __width)] = new Simple(*this, Position(x, y), energy);
    }

    void Game::addStrategic(const Position &position, Strategy *s) {
        if (__grid[position.x + (position.y * __width)]) throw PositionNonemptyEx(position.x, position.y);
        if (position.x >= __width || position.y >= __height) throw OutOfBoundsEx(__width, __height, position.x, position.y);

        __grid[position.x + (position.y * __width)] = new Strategic(*this, position, STARTING_AGENT_ENERGY, s);
    }

    void Game::addStrategic(unsigned x, unsigned y, Strategy *s) {
        if (__grid[x + (y * __width)]) throw PositionNonemptyEx(x, y);
        if (x >= __width || y >= __height) throw OutOfBoundsEx(__width, __height, x, y);

        __grid[x + (y * __width)] = new Strategic(*this, Position(x, y), STARTING_AGENT_ENERGY, s);
    }

    void Game::addFood(const Position &position) {
        if (__grid[position.x + (position.y * __width)]) throw PositionNonemptyEx(position.x, position.y);
        if (position.x >= __width || position.y >= __height) throw OutOfBoundsEx(__width, __height, position.x, position.y);

        __grid[position.x + (position.y * __width)] = new Food(*this, position, STARTING_RESOURCE_CAPACITY);
    }

    void Game::addFood(unsigned x, unsigned y) {
        if (__grid[x + (y * __width)]) throw PositionNonemptyEx(x, y);
        if (x >= __width || y >= __height) throw OutOfBoundsEx(__width, __height, x, y);

        __grid[x + (y * __width)] = new Food(*this, Position(x, y), STARTING_RESOURCE_CAPACITY);
    }

    void Game::addAdvantage(const Position &position) {
        if (__grid[position.x + (position.y * __width)]) throw PositionNonemptyEx(position.x, position.y);
        if (position.x >= __width || position.y >= __height) throw OutOfBoundsEx(__width, __height, position.x, position.y);

        __grid[position.x + (position.y * __width)] = new Advantage(*this, position, STARTING_RESOURCE_CAPACITY);
    }

    void Game::addAdvantage(unsigned x, unsigned y) {
        if (__grid[x + (y * __width)]) throw PositionNonemptyEx(x, y);
        if (x >= __width || y >= __height) throw OutOfBoundsEx(__width, __height, x, y);

        __grid[x + (y * __width)] = new Advantage(*this, Position(x, y), STARTING_RESOURCE_CAPACITY);
    }

    const Surroundings Game::getSurroundings(const Position &pos) const {
        Surroundings sur;
        for (int i = 0; i < 9; ++i) {
            sur.array[i] = EMPTY;
        }
        for (int x = -1; x <= 1; ++x) {
            for (int y = -1; y <= 1; ++y) {
                if (x == 0 && y == 0) {
                    sur.array[4] = SELF;
                }
                if (pos.x + x >= 0 && pos.x + x < __width
                        && pos.y + y >= 0 && pos.y + y < __height) {
                    // In bounds
                    Piece *piece = __grid[pos.x + x + ((pos.y + y) * __width)];
                    if (piece)
                        sur.array[pos.x + x + ((pos.y + y) * __width)] = __grid[pos.x + x + ((pos.y + y) * __width)]->getType();

                    /*Strategic *stra = dynamic_cast<Strategic*>(piece);
                    if (stra)
                        sur.array[pos.x + x + ((pos.y + y) * __width)] = STRATEGIC;
                    else {
                        Simple *simple = dynamic_cast<Simple*>(piece);
                        if (simple)
                            sur.array[pos.x + x + ((pos.y + y) * __width)] = SIMPLE;
                        else {
                            Food *food = dynamic_cast<Food*>(piece);
                            if (food)
                                sur.array[pos.x + x + ((pos.y + y) * __width)] = FOOD;
                            else {
                                Advantage *adv = dynamic_cast<Advantage*>(piece);
                                if (adv)
                                    sur.array[pos.x + x + ((pos.y + y) * __width)] = ADVANTAGE;
                            }
                        }
                    }*/
                }
                else {
                    // Out of bounds
                    sur.array[pos.x + x + ((pos.y + y) * __width)] = INACCESSIBLE;
                }
            }
        }

        return sur;
    }

    // gameplay methods
    const ActionType Game::reachSurroundings(const Position &from, const Position &to) { // note: STAY by default

    }

    bool Game::isLegal(const ActionType &ac, const Position &pos) const {

    }

    const Position Game::move(const Position &pos, const ActionType &ac) const { // note: assumes legal, use with isLegal()

    }

    void Game::round() {   // play a single round

    }

    void Game::play(bool verbose) {    // play game until over

    }

    std::ostream &operator<<(std::ostream &os, const Game &game) {

    }
}