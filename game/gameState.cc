#include <memory>
#include <utility>
#include <iostream>
#include <algorithm>

#include "game.h"
#include "gameState.h"
#include "board.h"
#include "../data/position.h"
#include "../data/pieceType.h"
#include "../moveable/moveable.h"
#include "../moveable/pieceFactory.h"

using namespace std;

GameState::GameState(int boardWidth, int boardHeight) : board{make_unique<Board>(boardWidth, boardHeight)}, currentPlayer{0} {}

GameState::GameState(const GameState &o) : board{make_unique<Board>(*o.board)}, currentPlayer{o.currentPlayer} {}

// TODO: multiple piece movements?
bool GameState::isValidMove(const Move &m) const
{
    // assuming move "target" is m.from[0]
    vector<Move> validMoves = board->getValidMoves(m.from[0], *this);
    return std::find(validMoves.begin(), validMoves.end(), m) != validMoves.end();
}

vector<Move> GameState::getValidMoves(const Position &pos) const
{
    if (isEmpty(pos))
        return vector<Move>{};
    return board->getValidMoves(pos, *this);
}

vector<Move> GameState::getValidMoves(int playerNum) const
{
    vector<Move> validMoves;
    for (int i = 0; i < board->getWidth(); i++)
    {
        for (int j = 0; j < board->getHeight(); j++)
        {
            Position pos{i, j};
            if (isEmpty(pos))
                continue;
            if (board->getPiece(pos).getOwner() == playerNum)
            {
                vector<Move> pieceValid = board->getValidMoves(pos, *this);
                validMoves.insert(pieceValid.end(), pieceValid.begin(), pieceValid.end());
            }
        }
    }
    return validMoves;
}

bool GameState::isOwner(Position p, int player) const
{
    if (isEmpty(p))
        return false;
    return board->getOwner(p) == player;
}

bool GameState::isEmpty(Position p) const
{
    return board->isEmpty(p);
}

bool GameState::isInBounds(Position p) const
{
    return p.x >= 0 && p.x < board->getWidth() && p.y >= 0 && p.y < board->getHeight();
}

void GameState::switchPlayers()
{
    currentPlayer = 1 - currentPlayer;
}

void GameState::setup(const Game &g)
{
    string cmd;
    string pieceType;
    string colour;

    while (cin >> cmd)
    {
        if (cmd == "done")
        {
            break; // TODO: make sure this is a valid board (2 kings, pawns in right pos, etc)
        }
        else if (cmd == "+")
        {
            cin >> pieceType;
            pair<PieceType, int> p = PieceTypeUtils::fromString(pieceType);
            Position pos;
            cin >> pos;

            board->addPiece(PieceFactory::createPiece(pos, p.first, p.second, board->getWidth(), board->getHeight()), pos);
            g.updateOutputs(Move{pos, pos});
        }
        else if (cmd == "-")
        {
            Position pos;
            cin >> pos;

            if (board->popPiece(pos))
            {
                g.updateOutputs(Move{pos,pos});
            }
        }
        else if (cmd == "=")
        {
            while (cin >> colour)
            {
                if (colour == "black" || colour == "white")
                {
                    break;
                }
                cout << "Invalid colour, use 'black'/'white'" << endl;
            }

            currentPlayer = (colour == "white") ? 0 : 1;
        }
        else
        {
            cout << "Invalid command" << endl;
        }
    }
}