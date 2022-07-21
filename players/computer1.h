#ifndef COMPUTER1_H_
#define COMPUTER1_H_

#include "player.h"

struct Move;
class GameState;
enum class PlayerColor;

class Computer1 : public Player
{
    Move doNextMove(const GameState &) override;

public:
    explicit Computer1(PlayerColor);
};

#endif // COMPUTER1_H_