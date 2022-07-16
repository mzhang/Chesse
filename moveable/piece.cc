#include <vector>
#include <memory>
#include "piece.h"
#include "../data/pieceType.h"
#include "../game/gameState.h"
#include "../data/move.h"

using namespace std;

Piece::Piece(int x, int y, PieceType type, int playerNum) : position{Position{x, y}}, type{type}, hasMoved{false}, playerNum{playerNum} {}

Piece::~Piece() {}

Position Piece::getPosition() { return position; }

vector<Move> Piece::getValidMoves(const GameState &g) {}

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
