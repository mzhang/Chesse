#ifndef GAMESTATE_H_
#define GAMESTATE_H_

#include <memory>

class Game;
class Position;
class Board;

struct GameState
{
    std::unique_ptr<Board> board;
    int currentPlayer; // white = 0; black = 1

    GameState(int, int);
    void setup(const Game &);

    bool isInBounds(Position p) const;
    bool isOwner(Position p, int player) const;
    bool isEmpty(Position p) const;

    void switchPlayers();
    
    friend std::istream &operator>>(std::istream &is, GameState &g);
};

#endif