#ifndef COMPUTER4_H_
#define COMPUTER4_H_

#include "player.h"

struct Move;
class GameState;

class Computer4 : public Player
{
    float evaluate(GameState &); // evaluate the board (based on piece values)
    Move doNextMove(const GameState &) override;
};

#endif // COMPUTER4_H_