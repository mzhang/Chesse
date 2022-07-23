#include <vector>

#include "output.h"
#include "../game/gameState.h"
#include "../data/position.h"

using namespace std;

void Output::update(const GameState &g, const Move &m)
{
    doUpdate(g, m);
}

bool Output::isBlackTile(const Position &p) {
    return (p.y % 2 == 0 && p.x % 2 == 0) || (p.y % 2 == 1 && p.x % 2 == 1);
}

void Output::displayValidMoves(const GameState &g, const vector<Move> &moves) {
    doDisplayValidMoves(g, moves);
}