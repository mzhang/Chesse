#ifndef GAME_H_
#define GAME_H_

#include <iostream>

class Board;

class Game
{
    const int width = 8;
    const int height = 8;

    Board *b;

public:
    Game();
    ~Game();
    void play();

    friend std::istream &operator>>(std::istream &in, const Game &g);
    friend std::ostream &operator<<(std::ostream &out, const Game &g);
};

#endif