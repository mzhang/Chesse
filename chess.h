#ifndef CHESS_H_
#define CHESS_H_

class Game;

class Chess
{
    Game *g;
public:
    Chess();
    ~Chess();
    void start();
};

#endif
