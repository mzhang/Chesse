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
    board.resize(width);
    for (int i = 0; i < width; i++)
    {
        board[i].resize(height);
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
    // TODO: implement
}

void Board::addPiece(Position p, PieceType type, int owner)
{
    board[p.x][p.y] = make_unique<Piece>(Piece{p.x, p.y, type, owner});
}

unique_ptr<Moveable> Board::popPiece(Position p)
{
    return std::move(board[p.x][p.y]);
}

void Board::setPiece(Position p, unique_ptr<Moveable> piece)
{
    board[p.x][p.y] = std::move(piece);
}

int Board::getOwner(Position p) const
{
    return board[p.x][p.y]->getOwner();
}

bool Board::isEmpty(Position p) const
{
    return !board[p.x][p.y];
}