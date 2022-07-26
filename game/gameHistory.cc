#include "gameHistory.h"
#include "../data/completedMove.h"
#include "../data/move.h"

#include <utility>

using namespace std;

void GameHistory::addMove(CompletedMove &&completedMove) {
  history.push_back(std::move(completedMove));
}

void GameHistory::printHistory() {
  // Print every move in the history
  for (const CompletedMove &completedMove : history) {
    cout << completedMove.move << endl;
  }
}

bool GameHistory::empty() { return history.empty(); }

Move GameHistory::getLastMove() {
  if (history.empty()) {
    return Move{};
  }
  return history.back().move;
}

CompletedMove GameHistory::pop_back() {
  // Pop the last move off the history
  auto last = std::move(history.back());
  history.pop_back();
  return last;
}
