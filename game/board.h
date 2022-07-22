#ifndef BOARD_H_
#define BOARD_H_
#include <vector>
#include <memory>

struct Moveable;
struct Position;
struct Move;
enum class PieceType;
class GameState;
enum class PlayerColor;

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

    Move makeMove(Move);

    void addPiece(std::unique_ptr<Moveable>, const Position &);
    std::unique_ptr<Moveable> popPiece(Position &);
    void setPiece(Position &, std::unique_ptr<Moveable>);
    const Moveable &getPiece(const Position &) const;

    PlayerColor getOwner(const Position &) const;
    PieceType getPieceType(const Position &) const;
    bool isEmpty(const Position &) const;

    int getWidth() const;
    int getHeight() const;

    void undoMove(Move m);

};

#endif
