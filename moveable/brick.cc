#include <vector>
#include <memory>

#include "brick.h"
#include "../data/pieceType.h"
#include "../game/gameState.h"
#include "../data/move.h"
#include "./piece.h"
#include "./moveable.h"
#include "decorator.h"
#include "../data/playerColor.h"

using namespace std;

Brick::Brick(unique_ptr<Moveable> component) : Decorator{std::move(component)} {}

Brick::Brick(const Brick &o) : Decorator{o} {}

vector<Position> Brick::getAttackedTiles(const GameState &g, bool checkChildren) const
{
    vector<Position> attackedTiles{};
    return attackedTiles;
}

vector<Move> Brick::getValidMoves(const GameState &g, bool checkChildren) const
{
    vector<Move> moves{};
    return moves;
}

unique_ptr<Moveable> Brick::clone() const
{
    return make_unique<Brick>(*this);
}
