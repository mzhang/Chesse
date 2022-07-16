#ifndef GAMESTATE_H_
#define GAMESTATE_H_

#include <memory>

class Board;

struct GameState
{
    std::unique_ptr<Board> board;
    int currentPlayer; // white = 0; black = 1

    GameState(int, int);
};

#endif