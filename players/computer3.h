#ifndef COMPUTER3_H_
#define COMPUTER3_H_

#include "player.h"

struct Move;
class GameState;

class Computer3 : public Player
{
    Move doNextMove(const GameState &) override;
};

#endif // COMPUTER3_H_