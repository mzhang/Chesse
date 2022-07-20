#include <vector>
#include <memory>
#include <iostream>

#include "board.h"
#include "../moveable/moveable.h"
#include "../moveable/piece.h"
#include "../data/position.h"
#include "../data/move.h"

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

PieceType Board::getPieceType(const Position &p) const
{
    return board[p.y][p.x]->getPieceType();
}

// kinda odd that board needs to be passed in a gamestate, but it's needed for the moveable's getValidMoves() function
// the debate is passing in a gs vs having hs be able to access arbitrary board positions(eg via board[][])
vector<Move> Board::getValidMoves(const Position &pos, GameState gs) const
{
    return board[pos.y][pos.x]->getValidMoves(gs);
}

void Board::makeMove(Move move)
{
    // pre: the move is valid
    for (Position capture : move.capturePositions)
    {
        popPiece(capture);
    }
    // assuming all pieces from Move::to have corresponding Move::from
    for (int i = 0; i < (int)move.to.size(); ++i)
    {
        board[move.to[i].y][move.to[i].x] = std::move(board[move.from[i].y][move.from[i].x]);
    }

    // vector<unique_ptr<Moveable>> from; // we need to store the pieces that will move since we may have a second piece overlapping
    // for (int i = 0; i < (int)move.from.size(); ++i)
    // {
    //     from.push_back(std::move(board[move.from[i].y][move.from[i].x]));
    // }

    // for (int i = 0; i < (int)move.to.size(); ++i)
    // {
    //     if (!isEmpty(move.to[i]))
    //     {
    //         popPiece(move.to[i]);
    //     }
    // }

    // for (int i = 0; i < (int)move.capturePositions.size(); ++i)
    // {
    //     if (!isEmpty(move.capturePositions[i]))
    //     {
    //         popPiece(move.capturePositions[i]);
    //     }
    // }

    // for (int i = 0; i < (int)move.from.size(); ++i)
    // {
    //     setPiece(move.to[i], std::move(from[i]));
    // }
}

void Board::addPiece(Position &p, PieceType type, int owner)
{
    unique_ptr<Moveable> piece = make_unique<Piece>(p.x, p.y, type, owner);
    if (type == PieceType::ROOK)
    {
        piece = make_unique<MoveX>(std::move(piece), width);
        piece = make_unique<MoveY>(std::move(piece), width);
    }
    else if (type == PieceType::KING)
    {
        piece = make_unique<MoveX>(std::move(piece), 1);
        piece = make_unique<MoveY>(std::move(piece), 1);
    }
    else if (type == PieceType::PAWN)
    {
        piece = make_unique<MoveY>(std::move(piece), 1);
    }
    board[p.y][p.x] = std::move(piece);
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