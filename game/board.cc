#include <vector>
#include <memory>
#include <iostream>

#include "board.h"
#include "../moveable/moveable.h"
#include "../moveable/piece.h"
#include "../data/position.h"
#include "../data/move.h"

using namespace std;

void Board::resizeBoard()
{
    board.resize(height);
    for (int i = 0; i < height; i++)
    {
        board[i].resize(width);
    }
}

Board::Board(int width, int height) : width{width}, height{height}
{
    resizeBoard();
}

Board::~Board() {}

void Board::swap(Board &o)
{
    std::swap(width, o.width);
    std::swap(height, o.height);
    std::swap(board, o.board);
}

Board::Board(const Board &o) : width{o.width}, height{o.height}
{
    resizeBoard();

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (board[i][j])
            { // if there is a piece at this position (aka not nullptr)
                board[i][j] = board[i][j]->clone();
            }
        }
    }
}

int Board::getWidth() const
{
    return width;
}

int Board::getHeight() const
{
    return height;
}

Board &Board::operator=(const Board &o)
{
    Board tmp{o};
    swap(tmp);

    return *this;
}

Board::Board(Board &&o) : width{o.width}, height{o.height}
{
    board = std::move(o.board);
    o.board.clear();
}

Board &Board::operator=(Board &&o)
{
    swap(o);

    return *this;
}

void Board::makeMove(Move move)
{
    // pre: the move is valid

    vector<unique_ptr<Moveable>> from; // we need to store the pieces that will move since we may have a second piece overlapping
    for (int i = 0; i < (int)move.from.size(); ++i) {
        from.push_back(std::move(board[move.from[i].y][move.from[i].x]));
    }

    for (int i = 0; i < (int)move.to.size(); ++i) {
        if (!isEmpty(move.to[i])) {
            popPiece(move.to[i]);
        }
        
    }

    for (int i = 0; i < (int)move.capturePositions.size(); ++i) {
        if (!isEmpty(move.capturePositions[i])) {
            popPiece(move.capturePositions[i]);
        }
    }

    for (int i = 0; i < (int)move.from.size(); ++i) {
        setPiece(move.to[i], std::move(from[i]));
    }

}

void Board::addPiece(Position &p, PieceType type, int owner)
{
    board[p.y][p.x] = make_unique<Piece>(Piece{p.x, p.y, type, owner});
}

unique_ptr<Moveable> Board::popPiece(Position &p)
{
    return std::move(board[p.y][p.x]);
}

void Board::setPiece(Position &p, unique_ptr<Moveable> piece)
{
    board[p.y][p.x] = std::move(piece);
}

Moveable &Board::getPiece(const Position &p) const
{
    return *board[p.y][p.x];
}

int Board::getOwner(const Position &p) const
{
    return board[p.y][p.x]->getOwner();
}

bool Board::isEmpty(const Position &p) const
{
    return !board[p.y][p.x];
}