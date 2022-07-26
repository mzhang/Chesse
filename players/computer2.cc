#include "computer2.h"
#include "../data/move.h"
#include "../data/playerColor.h"
#include "../game/board.h"
#include "../game/gameState.h"

#include <random>
#include <vector>

using namespace std;

Computer2::Computer2(PlayerColor color) : Player{color} {}

bool Computer2::isCapturingMove(const GameState &state, const Move &move) {
  // cout << move.capturePositions.size() << endl;
  for (auto targetPos : move.capturePositions) {
    if (!state.isEmpty(targetPos) && state.getOwner(targetPos) != playerColor) {
      return true;
    }
  }
  return false;
}

bool Computer2::isCheckingMove(const GameState &state, const Move &move) {
  return state.isInCheckAfterMove(PlayerColorUtils::getNext(playerColor), move);
}

Move Computer2::doNextMove(const GameState &state) {
  // Get all possible moves
  auto possible_moves = state.getValidMoves(playerColor);
  vector<Move> preferred_moves = vector<Move>();

  // Add all possible moves that are capturing moves or checking moves to
  // preferred_moves
  for (auto move : possible_moves) {
    if (isCapturingMove(state, move) || isCheckingMove(state, move)) {
      preferred_moves.push_back(move);
    }
  }

  std::random_device rd;
  std::mt19937 generator{rd()};

  // If there are no capturing or checking moves, return a random move
  if (preferred_moves.size() == 0) {
    // cout << "No capturing or checking moves" << endl;
    std::uniform_int_distribution<int> distribution(0,
                                                    possible_moves.size() - 1);
    int random_index = distribution(generator);
    return possible_moves[random_index];
  } else {
    // If there are capturing or checking moves, return a random move from the
    // preferred moves
    std::uniform_int_distribution<int> distribution(0,
                                                    preferred_moves.size() - 1);
    int random_index = distribution(generator);
    return preferred_moves[random_index];
  }
}
