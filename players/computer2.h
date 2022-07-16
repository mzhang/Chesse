#ifndef COMPUTER2_H_
#define COMPUTER2_H_

#include "../game/gameState.h"
#include "../data/move.h"
#include "player.h"

class Computer2 : public Player
{
    Move doNextMove(GameState &) override;
};

#endif // COMPUTER2_H_