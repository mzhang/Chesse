#include <vector>
#include <memory>
#include "piece.h"
#include "../data/pieceType.h"
#include "../game/gameState.h"
#include "../data/move.h"
#include "../data/playerColor.h"

using namespace std;

Piece::Piece(int x, int y, PieceType pieceType, PlayerColor color) : playerColor{color}, type{pieceType}, movedCount{0}, position{Position{x, y}} {}

Piece::~Piece() {}

Position Piece::getPosition() const
{
    return position;
}
void Piece::setPosition(Position pos)
{
    position = pos;
}

int Piece::getMovedCount() const
{
    return movedCount;
}
void Piece::incMovedCount()
{
    movedCount++;
}

vector<Move> Piece::getValidMoves(const GameState &g) const
{
    return vector<Move>{};
}

PieceType Piece::getPieceType() const
{
    return type;
}

PlayerColor Piece::getOwner() const
{
    return playerColor;
}

unique_ptr<Moveable> Piece::clone() const
{
    return make_unique<Piece>(*this);
}
