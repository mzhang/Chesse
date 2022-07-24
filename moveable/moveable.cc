#include <vector>
#include <memory>

#include "moveable.h"
#include "../data/position.h"
#include "../data/move.h"

using namespace std;

Moveable::Moveable() {}

Moveable::~Moveable() {}

vector<Position> Moveable::getAttackedTiles(const GameState &g) const
{
    vector<Position> tiles;
    for (const Move &move : getValidMoves(g))
    {
        tiles.insert(tiles.end(), move.to.begin(), move.to.end());
    }
    return tiles;
}