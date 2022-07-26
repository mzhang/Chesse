#ifndef TEXTDISPLAY_H_
#define TEXTDISPLAY_H_

#include "output.h"
#include <vector>

struct Position;
class GameState;

class TextDisplay : public Output {
  int boardWidth;
  int boardHeight;

  void doUpdate(const GameState &, const Move &) override;
  void doDisplayValidMoves(const GameState &,
                           const std::vector<Move> &) override;

public:
  TextDisplay(int, int);
};
#endif
