//
// Created by Gavin on 4/10/2016.
//

#include <sstream>
#include <iomanip>
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

        __numInitAgents = (__width * __height) / NUM_INIT_AGENT_FACTOR;
        __numInitResources = (__width * __height) / NUM_INIT_RESOURCE_FACTOR;
        unsigned int numStrategic = __numInitAgents / 2;
        unsigned int numSimple = __numInitAgents - numStrategic;
        unsigned int numAdvantages = __numInitResources / 4;
        unsigned int numFoods = __numInitResources - numAdvantages;

        while (numStrategic > 0) {
            int i = d(gen);
            if (i != (__width * __height) && __grid[i] == nullptr) {
                Position pos(i / __width, i % __width);
                __grid[i] = new Strategic(*this, pos, STARTING_AGENT_ENERGY);
                numStrategic--;
            }
        }

        while (numSimple > 0) {
            int i = d(gen);
            if (i != (__width * __height) && __grid[i] == nullptr) {
                Position pos(i / __width, i % __width);
                __grid[i] = new Simple(*this, pos, STARTING_AGENT_ENERGY);
                numSimple--;
            }
        }

        while (numFoods > 0) {
            int i = d(gen);
            if (i != (__width * __height) && __grid[i] == nullptr) {
                Position pos(i / __width, i % __width);
                __grid[i] = new Food(*this, pos, STARTING_RESOURCE_CAPACITY);
                numFoods--;
            }
        }

        while (numAdvantages > 0) {
            int i = d(gen);
            if (i != (__width * __height) && __grid[i] == nullptr) {
                Position pos(i / __width, i % __width);
                __grid[i] = new Advantage(*this, pos, STARTING_RESOURCE_CAPACITY);
                numAdvantages--;
            }
        }
    }

    //PUBLIC
    //Constructors / Destructor
    Game::Game() : __width(3), __height(3) {
        for (unsigned i = 0; i < (__width * __height); ++i) {
            __grid.push_back(nullptr);
        }
        __status = NOT_STARTED;
        __verbose = false;
        __round = 0;
    }

    Game::Game(unsigned width, unsigned height, bool manual) : __width(width), __height(height) { // note: manual population by default
        if (width < MIN_WIDTH || height < MIN_HEIGHT) {
            throw InsufficientDimensionsEx(MIN_WIDTH, MIN_HEIGHT, width, height);
        }

        __status = NOT_STARTED;
        __verbose = false;
        __round = 0;

        for (unsigned i = 0; i < (__width * __height); ++i) {
            __grid.push_back(nullptr);
        }

        if (!manual) {
            populate();
        }
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
            if (simple) numAgents++;
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
            if (simple) numAgents++;
        }

        return numAgents;
    }

    const Piece *Game::getPiece(unsigned int x, unsigned int y) const {
        if (y >= __width || x >= __height) throw OutOfBoundsEx(__width, __height, x, y);
        if (__grid[y + (x * __width)] == nullptr) throw PositionEmptyEx(x, y);
        return __grid[y + (x * __width)];
    }

    // grid population methods
    void Game::addSimple(const Position &position) {
        int index = position.y + (position.x * __width);
        if (position.y >= __width || position.x >= __height) throw OutOfBoundsEx(__width, __height, position.x, position.y);
        if (__grid[index]) throw PositionNonemptyEx(position.x, position.y);

        __grid[index] = new Simple(*this, position, STARTING_AGENT_ENERGY);
    }

    void Game::addSimple(const Position &position, double energy) { // used for testing only
        int index = position.y + (position.x * __width);
        if (position.y >= __width || position.x >= __height) throw OutOfBoundsEx(__width, __height, position.x, position.y);
        if (__grid[index]) throw PositionNonemptyEx(position.x, position.y);

        __grid[index] = new Simple(*this, position, energy);
    }

    void Game::addSimple(unsigned x, unsigned y) {
        int index = y + (x * __width);
        if (y >= __width || x >= __height) throw OutOfBoundsEx(__width, __height, x, y);
        if (__grid[index]) throw PositionNonemptyEx(x, y);

        __grid[index] = new Simple(*this, Position(x, y), STARTING_AGENT_ENERGY);
    }

    void Game::addSimple(unsigned y, unsigned x, double energy) {
        int index = y + (x * __width);
        if (y >= __width || x >= __height) throw OutOfBoundsEx(__width, __height, x, y);
        if (__grid[index]) throw PositionNonemptyEx(x, y);

        __grid[index] = new Simple(*this, Position(x, y), energy);
    }

    void Game::addStrategic(const Position &position, Strategy *s) {
        int index = position.y + (position.x * __width);
        if (position.y >= __width || position.x >= __height) throw OutOfBoundsEx(__width, __height, position.x, position.y);
        if (__grid[index]) throw PositionNonemptyEx(position.x, position.y);

        __grid[index] = new Strategic(*this, position, STARTING_AGENT_ENERGY, s);
    }

    void Game::addStrategic(unsigned x, unsigned y, Strategy *s) {
        int index = y + (x * __width);
        if (y >= __width || x >= __height) throw OutOfBoundsEx(__width, __height, x, y);
        if (__grid[index]) throw PositionNonemptyEx(x, y);

        __grid[index] = new Strategic(*this, Position(x, y), STARTING_AGENT_ENERGY, s);
    }

    void Game::addFood(const Position &position) {
        int index = position.y + (position.x * __width);
        if (position.y >= __width || position.x >= __height) throw OutOfBoundsEx(__width, __height, position.x, position.y);
        if (__grid[index]) throw PositionNonemptyEx(position.x, position.y);

        __grid[index] = new Food(*this, position, STARTING_RESOURCE_CAPACITY);
    }

    void Game::addFood(unsigned x, unsigned y) {
        int index = y + (x * __width);
        if (y >= __width || x >= __height) throw OutOfBoundsEx(__width, __height, x, y);
        if (__grid[index]) throw PositionNonemptyEx(x, y);

        __grid[index] = new Food(*this, Position(x, y), STARTING_RESOURCE_CAPACITY);
    }

    void Game::addAdvantage(const Position &position) {
        int index = position.y + (position.x * __width);
        if (position.y >= __width || position.x >= __height) throw OutOfBoundsEx(__width, __height, position.x, position.y);
        if (__grid[index]) throw PositionNonemptyEx(position.x, position.y);

        __grid[index] = new Advantage(*this, position, STARTING_RESOURCE_CAPACITY);
    }

    void Game::addAdvantage(unsigned x, unsigned y) {
        int index = y + (x * __width);
        if (y >= __width || x >= __height) throw OutOfBoundsEx(__width, __height, x, y);
        if (__grid[index]) throw PositionNonemptyEx(x, y);

        __grid[index] = new Advantage(*this, Position(x, y), STARTING_RESOURCE_CAPACITY);
    }

    const Surroundings Game::getSurroundings(const Position &pos) const {
        //std::cout << "Getting surroundings..." << std::endl;
        Surroundings sur;
        for (int i = 0; i < 9; ++i) {
            sur.array[i] = EMPTY;
        }
        for (int row = -1; row <= 1; ++row) {
            for (int col = -1; col <= 1; ++col) {
                if (row == 0 && col == 0) {
                    sur.array[col + 1 + ((row + 1) * __width)] = SELF;
                }
                if (pos.x + row >= 0 && pos.x + row < __height
                        && pos.y + col >= 0 && pos.y + col < __width) {
                    // In bounds
                    unsigned int index = pos.y + col + ((pos.x + row) * __width);
                    //Piece *piece = __grid[pos.y + y + ((pos.x + x) * __width)];
                    if (__grid[index])
                        sur.array[col + 1 + ((row + 1) * __width)] = __grid[index]->getType();
                }
                else {
                    // Out of bounds
                    sur.array[col + 1 + ((row + 1) * __width)] = INACCESSIBLE;
                }
            }
        }

        return sur;
    }

    // gameplay methods
    const ActionType Game::reachSurroundings(const Position &from, const Position &to) { // note: STAY by default
        return ActionType::STAY;
    }

    bool Game::isLegal(const ActionType &ac, const Position &pos) const {
        int x, y;
        x = pos.x;
        y = pos.y;
        switch (ac) {
            case E: y++; break;
            case NE: y++; x--; break;
            case N: x--; break;
            case NW: y--; x--; break;
            case W: y--; break;
            case SW: y--; x++; break;
            case S: x++; break;
            case SE: x++; y++; break;
        }
        Position p((unsigned )x, (unsigned)y);
        if (p.x < __height && p.y < __width && !getPiece(p.x, p.y))
            return true;
    }

    const Position Game::move(const Position &pos, const ActionType &ac) const { // note: assumes legal, use with isLegal()
        if (isLegal(ac, pos)) {
            int x, y;
            x = pos.x;
            y = pos.y;
            switch (ac) {
                case E: y++; break;
                case NE: y++; x--; break;
                case N: x--; break;
                case NW: y--; x--; break;
                case W: y--; break;
                case SW: y--; x++; break;
                case S: x++; break;
                case SE: x++; y++; break;
            }
            Position p((unsigned )x, (unsigned)y);
            return p;
            //__grid[(unsigned)y + ((unsigned)x * __height)] = __grid[pos.y + (pos.x * __width)];
            //__grid[pos.y + (pos.x * __width)] = nullptr;
        }
    }

    void Game::round() {   // play a single round

    }

    void Game::play(bool verbose) {    // play game until over

    }

    std::ostream &operator<<(std::ostream &os, const Game &game) {
        os << "Round " << game.__round << std::endl;
        int column = 0;
        for (auto it = game.__grid.begin(); it != game.__grid.end(); ++it) {
            if (*it == nullptr) {
                os << "[" << std::setw(6) << "]";
            } else {
                //os ;
                std::stringstream ss;
                ss << "[" << **it;
                std::string str;
                std::getline(ss, str);
                //os << str << std::setw(3) << "]";
                os << str << "]";
                //os << std::setw(4) << "[" << **it;
                //os << "]";
                //os ;
            }
            if (++column == game.__width) {
                column = 0;
                os << std::endl;
            }
        }
        os << "Status: " << game.getStatus() << "..." << std::endl;
        return os;
    }
}