#include <vector>
#include <memory>
#include "piece.h"
#include "../data/pieceType.h"
#include "../game/gameState.h"
#include "../data/move.h"

using namespace std;

Piece::Piece(int x, int y, PieceType pieceType, int pNum) :  playerNum{pNum}, type{pieceType}, hasMoved{false}, position{Position{x, y}} {}

Piece::~Piece() {}

Position Piece::getPosition() { return position; }

vector<Move> Piece::getValidMoves(const GameState &g)
{
    return vector<Move>{};
}

PieceType Piece::getPieceType()
{
    return type;
}

int Piece::getOwner()
{
    return playerNum;
}

unique_ptr<Moveable> Piece::clone()
{
    return make_unique<Piece>(*this);
}
