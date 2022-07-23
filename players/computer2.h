#ifndef COMPUTER2_H_
#define COMPUTER2_H_

#include "player.h"

struct Move;
class GameState;

class Computer2 : public Player
{
    Move doNextMove(const GameState &) override;
    bool isCapturingMove(const GameState &, const Move &);
    bool isCheckingMove(const GameState &, const Move &);
public:
    explicit Computer2(PlayerColor);
};

#endif // COMPUTER2_H_