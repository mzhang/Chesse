#ifndef PIECE_H_
#define PIECE_H_

#include <vector>

#include "../data/pieceType.h"
#include "../data/playerColor.h"
#include "../data/position.h"
#include "moveable.h"

class Board;
enum class PieceType;
class GameState;

class Piece : public Moveable {
  PlayerColor playerColor;
  PieceType type;
  int movedCount;
  Position position;

protected:
public:
  Piece(int, int, PieceType, PlayerColor);
  ~Piece();

  PieceType getPieceType() const override;
  Position getPosition() const override;
  int getMovedCount() const override;
  PlayerColor getOwner() const override;
  std::vector<Move> getValidMoves(const GameState &, bool) const override;
  std::vector<Position> getAttackedTiles(const GameState &,
                                         bool) const override;

  std::unique_ptr<Moveable> clone() const override;

  void onMove(const Move &move, const Position &pos, bool,
              int movedCountDelta) override;
};
#endif
