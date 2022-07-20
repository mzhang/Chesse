#include "human.h"
#include "../game/gameState.h"
#include "../data/move.h"

using namespace std;

Human::Human(int playerNum) : Player{playerNum}
{
}

Move Human::doNextMove(const GameState &g)
{
    Position from;
    Position to;

    cin >> from;
    cin >> to;

    // TODO: right now this doesn't handle captures/castling. We should do some post-processing on move to handle this.

    // TODO: should check if this is actually a valid move...

    return Move{from, to};
}
