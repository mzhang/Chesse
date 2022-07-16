#ifndef BOARD_H_
#define BOARD_H_
#include <vector>
#include <memory>

class Moveable;
class Position;
class Move;
enum class PieceType;

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

    void addPiece(Position, PieceType, int);
    std::unique_ptr<Moveable> popPiece(Position);
    void setPiece(Position, std::unique_ptr<Moveable>);

    int getOwner(Position) const;
    bool isEmpty(Position) const;

    int getWidth() const;
    int getHeight() const;
};

#endif
