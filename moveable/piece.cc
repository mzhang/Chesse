#include "piece.h"
#include "../data/move.h"
#include "../data/pieceType.h"
#include "../data/playerColor.h"
#include "../game/gameState.h"
#include <memory>
#include <vector>

using namespace std;

Piece::Piece(int x, int y, PieceType pieceType, PlayerColor color)
    : playerColor{color}, type{pieceType}, movedCount{0}, position{
                                                              Position{x, y}} {}

Piece::~Piece() {}

Position Piece::getPosition() const { return position; }

int Piece::getMovedCount() const { return movedCount; }

vector<Move> Piece::getValidMoves(const GameState &g, bool) const {
  return vector<Move>{};
}

PieceType Piece::getPieceType() const { return type; }

vector<Position> Piece::getAttackedTiles(const GameState &, bool) const {
  return vector<Position>{};
}

PlayerColor Piece::getOwner() const { return playerColor; }

unique_ptr<Moveable> Piece::clone() const { return make_unique<Piece>(*this); }

void Piece::onMove(const Move &move, const Position &pos, bool,
                   int movedCountDelta) {
  position = pos;
  movedCount += movedCountDelta;
}
