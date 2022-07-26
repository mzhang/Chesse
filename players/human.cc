#include "human.h"
#include "../data/move.h"
#include "../game/gameState.h"

using namespace std;

Human::Human(PlayerColor color) : Player{color} {}

bool Human::isHeadless() const { return false; }

Move Human::doNextMove(const GameState &g) {
  Position from;
  Position to;

  while (cin >> from >> to) {
    // Validate that from and to are valid positions using g.isInBounds()
    if (!(g.isInBounds(from) && g.isInBounds(to))) {
      cout << "Invalid move! Please re-enter new positions. " << endl;
      continue;
    }

    Move move = Move{from, to};
    vector<Move> validMoves = g.getValidMoves(from);

    for (Move m : validMoves) {
      if (move.isSubset(m) && g.isOwner(from, playerColor)) {
        return m;
      }
    }

    cout << "Invalid move! Please re-enter new positions. " << endl;
  }

  return Move{};
}
