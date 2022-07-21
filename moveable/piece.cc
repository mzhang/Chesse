#include <vector>
#include <memory>
#include "piece.h"
#include "../data/pieceType.h"
#include "../game/gameState.h"
#include "../data/move.h"

using namespace std;

Piece::Piece(int x, int y, PieceType pieceType, int pNum) :  playerNum{pNum}, type{pieceType}, hasMoved{false}, position{Position{x, y}} {}

Piece::~Piece() {}

Position Piece::getPosition() const { return position; }

vector<Move> Piece::getValidMoves(const GameState &g) const
{
    return vector<Move>{};
}

PieceType Piece::getPieceType() const
{
    return type;
}

int Piece::getOwner() const
{
    return playerNum;
}

unique_ptr<Moveable> Piece::clone() const
{
    return make_unique<Piece>(*this);
}
