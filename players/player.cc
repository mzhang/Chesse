#include "player.h"
#include "../data/move.h"
#include "../game/gameState.h"

using namespace std;

Player::Player(PlayerColor color) : playerColor{color} {}

bool Player::isHeadless() const { return true; }

Move Player::nextMove(const GameState &g) { return doNextMove(g); }
