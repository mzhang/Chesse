#ifndef COMPUTER_H_
#define COMPUTER_H_

class GameState;
struct Move;

class Player
{
    virtual Move doNextMove(const GameState &) = 0;
protected:
    int playerNum;
public:
    explicit Player(int);

    Move nextMove(const GameState &);
};

#endif // COMPUTER_H_