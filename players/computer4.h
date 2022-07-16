#ifndef COMPUTER4_H_
#define COMPUTER4_H_

#include "../game/gameState.h"
#include "../data/move.h"
#include "player.h"

class Computer4 : public Player
{
    float evaluate(GameState &); // evaluate the board (based on piece values)
    Move doNextMove(GameState &) override;
};

#endif // COMPUTER4_H_