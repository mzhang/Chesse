#ifndef COMPUTER4_H_
#define COMPUTER4_H_

#include "player.h"

class Move;
class GameState;

class Computer4 : public Player
{
    float evaluate(GameState &); // evaluate the board (based on piece values)
    Move doNextMove(GameState &) override;
};

#endif // COMPUTER4_H_