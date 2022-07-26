#ifndef GAMEHISTORY_H_
#define GAMEHISTORY_H_

#include <vector>

#include "../data/completedMove.h"
#include "../game/gameState.h"

class GameHistory {
  std::vector<CompletedMove> history;

public:
  void addMove(CompletedMove &&);
  void printHistory();
  bool empty();
  CompletedMove pop_back();
  Move getLastMove();
};

#endif
