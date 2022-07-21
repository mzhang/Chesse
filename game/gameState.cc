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
    if (isEmpty(m.from[0]))
        return false;

    const Moveable &piece = board->getPiece(m.from[0]);
    vector<Move> validMoves = piece.getValidMoves(*this);
    return std::find(validMoves.begin(), validMoves.end(), m) != validMoves.end();
}

vector<Move> GameState::getValidMoves(const Position &pos) const
{
    if (isEmpty(pos))
        return vector<Move>{};
    
    const Moveable &piece = board->getPiece(pos);
    vector<Move> validMoves = piece.getValidMoves(*this);
    return validMoves;
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
                vector<Move> pieceValid = getValidMoves(pos);
                validMoves.insert(validMoves.end(), pieceValid.begin(), pieceValid.end());
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
        else if (cmd == "standard") {
            standard_chess_board();
            Move m;
            // Add the bottom and top two rows to m.from
            for (int i = 0; i < board->getWidth(); i++)
            {
                m.from.push_back({i, 0});
                m.from.push_back({i, 1});
                m.from.push_back({i, board->getHeight() - 1});
                m.from.push_back({i, board->getHeight() - 2});
            }
            g.updateOutputs(m);
        } else if (cmd == "+")
        {
            cin >> pieceType;
            pair<PieceType, int> p = PieceTypeUtils::fromString(pieceType);
            Position pos;
            cin >> pos;

            if (!isInBounds(pos))
            {
                cout << "Invalid position" << endl;
                continue;
            }

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

void GameState::standard_chess_board() {
    // Setup a standard chess board with pieces
    
    // Add 8 pawns to white
    for (int i = 0; i < 8; i++) {
        board->addPiece(PieceFactory::createPiece(Position{i, 1}, PieceType::PAWN, 0,
            board->getWidth(), board->getHeight()), Position{i, 1});
    }

    // Add 8 pawns to black
    for (int i = 0; i < 8; i++) {
        board->addPiece(PieceFactory::createPiece(Position{i, 6}, PieceType::PAWN,
            1, board->getWidth(), board->getHeight()), Position{i, 6});
    }

    // Add 2 rooks to white
    board->addPiece(PieceFactory::createPiece(Position{0, 0}, PieceType::ROOK, 0,
        board->getWidth(), board->getHeight()), Position{0, 0});
    board->addPiece(PieceFactory::createPiece(Position{7, 0}, PieceType::ROOK, 0,
        board->getWidth(), board->getHeight()), Position{7, 0});

    // Add 2 rooks to black
    board->addPiece(PieceFactory::createPiece(Position{0, 7}, PieceType::ROOK, 1,
        board->getWidth(), board->getHeight()), Position{0, 7});
    board->addPiece(PieceFactory::createPiece(Position{7, 7}, PieceType::ROOK, 1,
        board->getWidth(), board->getHeight()), Position{7, 7});

    // Add 2 knights to white
    board->addPiece(PieceFactory::createPiece(Position{1, 0}, PieceType::KNIGHT, 0,
        board->getWidth(), board->getHeight()), Position{1, 0});
    board->addPiece(PieceFactory::createPiece(Position{6, 0}, PieceType::KNIGHT, 0,
        board->getWidth(), board->getHeight()), Position{6, 0});

    // Add 2 knights to black
    board->addPiece(PieceFactory::createPiece(Position{1, 7}, PieceType::KNIGHT, 1,
        board->getWidth(), board->getHeight()), Position{1, 7});
    board->addPiece(PieceFactory::createPiece(Position{6, 7}, PieceType::KNIGHT, 1,
        board->getWidth(), board->getHeight()), Position{6, 7});

    // Add 2 bishops to white
    board->addPiece(PieceFactory::createPiece(Position{2, 0}, PieceType::BISHOP, 0,
        board->getWidth(), board->getHeight()), Position{2, 0});
    board->addPiece(PieceFactory::createPiece(Position{5, 0}, PieceType::BISHOP, 0,
        board->getWidth(), board->getHeight()), Position{5, 0});

    // Add 2 bishops to black
    board->addPiece(PieceFactory::createPiece(Position{2, 7}, PieceType::BISHOP, 1,
        board->getWidth(), board->getHeight()), Position{2, 7});
    board->addPiece(PieceFactory::createPiece(Position{5, 7}, PieceType::BISHOP, 1,
        board->getWidth(), board->getHeight()), Position{5, 7});

    // Add 1 queen to white
    board->addPiece(PieceFactory::createPiece(Position{3, 0}, PieceType::QUEEN, 0,
        board->getWidth(), board->getHeight()), Position{3, 0});

    // Add 1 queen to black
    board->addPiece(PieceFactory::createPiece(Position{3, 7}, PieceType::QUEEN, 1,
        board->getWidth(), board->getHeight()), Position{3, 7});

    // Add 1 king to white
    board->addPiece(PieceFactory::createPiece(Position{4, 0}, PieceType::KING, 0,
        board->getWidth(), board->getHeight()), Position{4, 0});

    // Add 1 king to black
    board->addPiece(PieceFactory::createPiece(Position{4, 7}, PieceType::KING, 1,
        board->getWidth(), board->getHeight()), Position{4, 7});
}
