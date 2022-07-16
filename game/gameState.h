#ifndef GAMESTATE_H_
#define GAMESTATE_H_

#include <memory>

class Position;
class Board;

struct GameState
{
    std::unique_ptr<Board> board;
    int currentPlayer; // white = 0; black = 1

    GameState(int, int);
    bool isInBounds(Position p) const;
    bool isOwner(Position p, int player) const;
    bool isEmpty(Position p) const;
};

#endif