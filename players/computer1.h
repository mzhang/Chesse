#ifndef COMPUTER1_H_
#define COMPUTER1_H_

#include "player.h"

struct Move;
class GameState;

class Computer1 : public Player
{
    Move doNextMove(const GameState &) override;
public:
    explicit Computer1(int);
};

#endif // COMPUTER1_H_