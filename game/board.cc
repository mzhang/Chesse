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
            if (board[i][j]) { // if there is a piece at this position (aka not nullptr)
                board[i][j] = board[i][j]->clone();
            }
        }
    }
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

vector<Position> Board::getValidMoves(int x, int y) {
    return board[x][y] ? board[x][y]->doGetValidMoves(*this) : vector<Position>{};
}

void Board::makeMove(Move move) {
    // TODO: implement
}

void Board::addPiece(int x, int y)
{
    cout << "addPiece(" << x << ", " << y << ")" << endl;
    board[x][y] = make_unique<Piece>(Piece{});
}

unique_ptr<Moveable> Board::getPiece(int x, int y)
{
    if (!board[x][y]) { // if there is no piece at this position, create a new one
        addPiece(x, y);
    }

    return std::move(board[x][y]);
}

void Board::setPiece(int x, int y, Moveable *piece)
{
    cout << "setPiece(" << x << ", " << y << ")" << endl;
    board[x][y] = unique_ptr<Moveable>{piece};
}