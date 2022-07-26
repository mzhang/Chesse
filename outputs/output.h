#ifndef OUTPUT_H_
#define OUTPUT_H_

#include <vector>

class GameState;
struct Position;
struct Move;

class Output {
  virtual void doUpdate(const GameState &, const Move &) = 0;
  virtual void doDisplayValidMoves(const GameState &,
                                   const std::vector<Move> &) = 0;

protected:
  bool isBlackTile(const Position &);

public:
  void update(const GameState &, const Move &);
  void displayValidMoves(const GameState &, const std::vector<Move> &);
};

#endif
