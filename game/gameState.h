#ifndef GAMESTATE_H_
#define GAMESTATE_H_

#include <memory>
#include <vector>

class Game;
class Position;
class Board;
class Move;

struct GameState
{
    std::unique_ptr<Board> board;
    int currentPlayer; // white = 0; black = 1

    GameState(int, int);
    GameState(const GameState &o);
    void setup(const Game &);

    bool isValidMove(const Move &m) const;
    bool isInBounds(Position p) const;
    bool isOwner(Position p, int player) const;
    bool isEmpty(Position p) const;
    std::vector<Move> getValidMoves(const Position &pos) const;

    void switchPlayers();

    friend std::istream &operator>>(std::istream &is, GameState &g);
};

#endif