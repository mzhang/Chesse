#include <iostream>
#include <memory>
#include <vector>

#include "../data/move.h"
#include "../data/pieceType.h"
#include "../data/position.h"
#include "../game/board.h"
#include "decorator.h"
#include "moveable.h"

using namespace std;

Decorator::Decorator(unique_ptr<Moveable> c) : component{std::move(c)} {}

Decorator::Decorator(const Decorator &o) : component{o.component->clone()} {}

Decorator::~Decorator(){};

PieceType Decorator::getPieceType() const { return component->getPieceType(); }

vector<Move> Decorator::getValidMoves(const GameState &gameState,
                                      bool checkChildren) const {
  return component->getValidMoves(gameState, checkChildren);
}

vector<Position> Decorator::getAttackedTiles(const GameState &gameState,
                                             bool checkSelf) const {
  vector<Position> tiles = component->getAttackedTiles(gameState);
  if (checkSelf) {
    for (const Move &move : getValidMoves(gameState, false)) {
      tiles.insert(tiles.end(), move.to.begin(), move.to.end());
    }
  }
  return tiles;
}

Position Decorator::getPosition() const { return component->getPosition(); }

int Decorator::getMovedCount() const { return component->getMovedCount(); }

void Decorator::setComponent(unique_ptr<Moveable> c) {
  component = std::move(c);
}

PlayerColor Decorator::getOwner() const { return component->getOwner(); }

void Decorator::onMove(const Move &move, const Position &endPos, bool headless,
                       int movedCountDelta) {
  component->onMove(move, endPos, headless, movedCountDelta);
}
