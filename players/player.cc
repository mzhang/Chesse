#include "player.h"
#include "../game/gameState.h"
#include "../data/move.h"

using namespace std;

Player::Player(int playerNum) : playerNum(playerNum)
{
}

Move Player::nextMove(GameState &g)
{
    return doNextMove(g);
}