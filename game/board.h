#ifndef BOARD_H_
#define BOARD_H_
#include <vector>
#include <memory>

class Moveable;
class Position;
class Move;

class Board
{
    int width;
    int height;

    std::vector<std::vector<std::unique_ptr<Moveable>>> board;

    void swap(Board &);
    void resizeBoard();

public:
    Board(int, int);
    ~Board();

    Board(const Board &);
    Board &operator=(const Board &);
    Board(Board &&);
    Board &operator=(Board &&);

    void makeMove(Move);

    void addPiece(int, int);
    Moveable *getPiece(int, int);
    void setPiece(int, int, Moveable *);
    std::vector<Position> getValidMoves(int, int);
};

#endif
