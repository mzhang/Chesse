#include "player.h"
#include "../game/gameState.h"
#include "../data/move.h"

using namespace std;

Player::Player(PlayerColor color) : playerColor{color}
{
}

bool Player::isHeadless() const
{
    return true;
}

Move Player::nextMove(const GameState &g)
{
    return doNextMove(g);
}
