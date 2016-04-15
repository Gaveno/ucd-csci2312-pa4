#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "ErrorContext.h"
#include "GamingTests.h"
#include "Game.h"
#include "Simple.h"
#include "Gaming.h"

using std::cout;
using std::endl;

using namespace Testing;

int main() {

    Gaming::Game g(3,3, 1);
    g.addSimple(0, 0);
    g.addSimple(1, 0);
    g.addFood(1, 2);
    //g.addStrategic(2, 0);
    g.addAdvantage(2, 2);
    //cout << g;
    g.play(true);

    const int NumIters = 3;

    cout << endl << "Testing PA5!!" << endl << endl;

    cout << "NOTE:  If you see any memory errors, you MUST fix them!" << endl;
    cout << "       Tests intentionally invoke destructors after they complete,"
    << endl;
    cout << "       so if you see a seg-fault after a passed test, it is"
    << endl;
    cout << "       probably a bug in your destructor." << endl;

    cout << endl;

    ErrorContext ec(cout);

    // piece tests
    test_piece_smoketest(ec);
    test_piece_print(ec, NumIters);
    test_piece_aging(ec, NumIters);
    test_piece_energy(ec, NumIters);
    test_piece_turntaking(ec, NumIters);
    test_piece_interaction(ec, NumIters);

    // surroundings tests
    test_surroundings_smoketest(ec);

    // action tests
    test_action_smoketest(ec);

    // game tests
    test_game_smoketest(ec);
    test_game_populate(ec, NumIters);
    test_game_getpiece(ec, NumIters);
    test_game_print(ec, NumIters);
    test_game_randomization(ec, NumIters);
    test_game_play(ec, NumIters);

    return 0;
}