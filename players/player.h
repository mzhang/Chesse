#ifndef COMPUTER_H_
#define COMPUTER_H_

#include "../game/board.h"
#include "../data/move.h"

class Player
{
    virtual Move doNextMove(Board &b) = 0;
protected:
    int playerNum;
public:
    explicit Player(int);

    Move nextMove(Board &b);
};

#endif // COMPUTER_H_