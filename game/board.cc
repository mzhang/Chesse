#include <vector>
#include <memory>
#include <iostream>

#include "board.h"
#include "../moveable/moveable.h"
#include "../moveable/piece.h"
#include "../data/position.h"
#include "../data/move.h"
#include "../data/completedMove.h"

#include "../moveable/moveX.h"
#include "../moveable/moveY.h"
#include "gameState.h"

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

    // cout << "DEBUG: Board copy constructor. Make sure this is intended" << endl;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (o.board[i][j])
            { // if there is a piece at this position (aka not nullptr)
                board[i][j] = o.board[i][j]->clone();
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

PieceType Board::getPieceType(const Position &p) const
{
    return isEmpty(p) ? PieceType::NONE : board[p.y][p.x]->getPieceType();
}

int Board::getMovedCount(const Position &p) const
{
    return isEmpty(p) ? 0 : board[p.y][p.x]->getMovedCount();
}

CompletedMove Board::makeMove(Move move, bool headless)
{
    // pre: the move is valid

    vector<unique_ptr<Moveable>> from; // we need to store the pieces that will move since we may have a second piece overlapping
    vector<pair<Position, unique_ptr<Moveable>>> capturedPieces;
    for (int i = 0; i < (int)move.from.size(); ++i)
    {
        from.push_back(std::move(board[move.from[i].y][move.from[i].x]));
    }

    for (int i = 0; i < (int)move.capturePositions.size(); ++i)
    {
        if (!isEmpty(move.capturePositions[i]))
        {
            capturedPieces.emplace_back(make_pair(move.capturePositions[i], popPiece(move.capturePositions[i])));
        }
    }

    for (int i = 0; i < (int)move.to.size(); ++i)
    {
        if (!isEmpty(move.to[i]))
        {
            popPiece(move.to[i]);
        }
    }

    for (int i = 0; i < (int)move.from.size(); ++i)
    {
        setPiece(move.to[i], std::move(from[i]));
        board[move.to[i].y][move.to[i].x]->onMove(move, move.to[i], headless);
    }

    return CompletedMove{move, std::move(capturedPieces)};
}

void Board::undoMove(CompletedMove &&m) 
{
    // Undoes the move and places any captured pieces back on the board

    // Move all the pieces back to their original positions
    for (size_t i = 0; i < m.move.from.size(); i++)
    {
        // Move objects from end position to starting position
        setPiece(m.move.from[i], popPiece(m.move.to[i]));
        board[m.move.from[i].y][m.move.from[i].x]->onMove(m.move, m.move.from[i], true, -1);
    }

    // Put back any captured pieces
    for (size_t i = 0; i < m.capturedPieces.size(); i++)
    {
        setPiece(m.capturedPieces[i].first, std::move(m.capturedPieces[i].second));
        board[m.capturedPieces[i].first.y][m.capturedPieces[i].first.x]->onMove(m.move, m.capturedPieces[i].first, true, 0);
    }
}

void Board::addPiece(unique_ptr<Moveable> piece, const Position &pos)
{
    board[pos.y][pos.x] = std::move(piece);
}

unique_ptr<Moveable> Board::popPiece(const Position &p)
{
    return std::move(board[p.y][p.x]);
}

void Board::setPiece(const Position &p, unique_ptr<Moveable> piece)
{
    board[p.y][p.x] = std::move(piece);
}

const Moveable &Board::getPiece(const Position &p) const
{
    return *board[p.y][p.x];
}

PlayerColor Board::getOwner(const Position &p) const
{
    return board[p.y][p.x]->getOwner();
}

bool Board::isEmpty(const Position &p) const
{
    // if this is not in bounds, throw an error
    if (p.y < 0 || p.y >= height || p.x < 0 || p.x >= width)
    {
        throw std::out_of_range("Position is out of bounds on board");
    }
    return !board[p.y][p.x];
}