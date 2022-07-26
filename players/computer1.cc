#include <iostream>
#include <random>

using namespace std;

#include "../data/move.h"
#include "../data/playerColor.h"
#include "../game/board.h"
#include "../game/gameState.h"
#include "computer1.h"

Computer1::Computer1(PlayerColor playerColor) : Player{playerColor} {}

Move Computer1::doNextMove(const GameState &state) {
  // Iterates over all pieces and all possible moves for each piece in
  // gamestate's board randomly chooses one and returns it
  auto possible_moves = state.getValidMoves(playerColor);

  // use uniform distribution to select a random move from the vector of
  // possible moves
  std::uniform_int_distribution<int> distribution(0, possible_moves.size() - 1);
  std::random_device rd;
  std::mt19937 generator{rd()};
  int random_index = distribution(generator);

  return possible_moves[random_index];
}
