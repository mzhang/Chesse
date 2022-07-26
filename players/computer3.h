#ifndef COMPUTER3_H_
#define COMPUTER3_H_

#include "player.h"

struct Move;
class GameState;
struct Position;

class Computer3 : public Player
{
    Move doNextMove(const GameState &) override;
    bool isCapturingMove(const GameState &, const Move &);
    bool isCheckingMove(const GameState &, const Move &);
    bool avoidsCapture(const GameState &, const Move &);

public:
    explicit Computer3(PlayerColor);
};

#endif // COMPUTER3_H_
