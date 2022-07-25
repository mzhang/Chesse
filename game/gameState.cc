#include <memory>
#include <utility>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

#include "game.h"
#include "gameState.h"
#include "board.h"
#include "../data/position.h"
#include "../data/pieceType.h"
#include "../moveable/moveable.h"
#include "../moveable/pieceFactory.h"
#include "../data/playerColor.h"

#include "../outputs/textDisplay.h"

#include <util.h>

using namespace std;

GameState::GameState(int boardWidth, int boardHeight) : board{make_unique<Board>(boardWidth, boardHeight)}, currentPlayer{PlayerColor::WHITE} {}

GameState::GameState(const GameState &o) : board{make_unique<Board>(*o.board)}, currentPlayer{o.currentPlayer} {}

GameState::~GameState() {}

void GameState::swap(GameState &o)
{
    std::swap(board, o.board);
    std::swap(currentPlayer, o.currentPlayer);
}

GameState &GameState::operator=(const GameState &o)
{
    GameState tmp{o};
    swap(tmp);
    return *this;
}

bool GameState::isValidMove(const Move &m) const
{
    // pre: m is not malformed
    Position mainPos = m.from[0];
    if (!isInBounds(mainPos) || isEmpty(mainPos))
    {
        return false;
    }

    const Moveable &piece = board->getPiece(mainPos);
    vector<Move> validMoves = piece.getValidMoves(*this);
    return std::find(validMoves.begin(), validMoves.end(), m) != validMoves.end() && !isInCheckAfterMove(piece.getOwner(), m);
}

// Precondition: move accounts for all side effects
void GameState::makeMove(const Move &m, bool headless)
{
    board->makeMove(m, headless);
    lastMove = m;
}

bool GameState::isInCheck(const PlayerColor &pc) const
{
    vector<Position> kingPos{};
    for (int i = 0; i < board->getWidth(); i++)
    {
        for (int j = 0; j < board->getHeight(); j++)
        {
            Position pos{i, j};
            if (!isEmpty(pos) && getPieceType(pos) == PieceType::KING && isOwner(pos, pc))
            {
                kingPos.emplace_back(pos);
            }
        }
    }
    return numberOfTilesAttacked(pc, kingPos) > 0;
}

// TODO: rename this to numberOfPiecesAttacking
// getEnemySightlines is expensive so we pass in vector to minimize calls
int GameState::numberOfTilesAttacked(const PlayerColor &pc, const vector<Position> &positions) const
{
    int numAttacked = 0;
    vector<Position> enemySightlines = getEnemySightlines(pc);
    for (const Position &pos : positions)
    {
        if (std::find(enemySightlines.begin(), enemySightlines.end(), pos) != enemySightlines.end())
        {
            ++numAttacked;
        }
    }
    return numAttacked;
}

bool GameState::isInCheckAfterMove(const PlayerColor &pc, const Move &m) const
{
    GameState tmp{*this};
    tmp.board->makeMove(m, true);
    return tmp.isInCheck(pc);
}

vector<Position> GameState::getEnemySightlines(const PlayerColor &pc) const
{
    vector<Position> sightline;
    for (int r = 0; r < board->getHeight(); r++)
    {
        for (int c = 0; c < board->getWidth(); c++)
        {
            Position pos{r, c};
            if (!isEmpty(pos) && !isOwner(pos, pc))
            {
                vector<Position> attackedTiles = board->getPiece(pos).getAttackedTiles(*this);
                sightline.insert(sightline.end(), attackedTiles.begin(), attackedTiles.end());
            }
        }
    }
    return sightline;
}

vector<Move> GameState::getValidMoves(const Position &pos) const
{

    // TODO: Reconcile this with checking for check
    // Avoid recursive checking for check

    if (isEmpty(pos))
    {
        return vector<Move>{};
    }

    const Moveable &piece = board->getPiece(pos);

    vector<Move> validMoves;
    vector<Move> pieceSightlines = piece.getValidMoves(*this);

    for (auto &move : pieceSightlines)
    {
        if (!isInCheckAfterMove(board->getOwner(pos), move))
        {
            validMoves.push_back(move);
        }
    }

    return validMoves;
}

vector<Move> GameState::getValidMoves(PlayerColor pc) const
{
    vector<Move> validMoves;
    for (int i = 0; i < board->getWidth(); i++)
    {
        for (int j = 0; j < board->getHeight(); j++)
        {
            Position pos{i, j};
            if (!isEmpty(pos) && isOwner(pos, pc))
            {
                vector<Move> pieceValidMoves = getValidMoves(pos);
                validMoves.insert(validMoves.end(), pieceValidMoves.begin(), pieceValidMoves.end());
            }
        }
    }
    return validMoves;
}

int GameState::getMovedCount(const Position &pos) const
{
    if (!isInBounds(pos) || isEmpty(pos))
    {
        return 0;
    }
    return board->getMovedCount(pos);
}

// todo: kill this
bool GameState::isOwner(const Position p, const PlayerColor playerColor) const
{
    if (!isInBounds(p) || isEmpty(p))
        return false;
    return board->getOwner(p) == playerColor;
}

PlayerColor GameState::getOwner(const Position &p) const
{
    if (!isInBounds(p) || isEmpty(p))
        return PlayerColor::NONE;
    return board->getOwner(p);
}

bool GameState::isEmpty(const Position p) const
{
    return board->isEmpty(p);
}

bool GameState::isInBounds(const Position p) const
{
    return p.x >= 0 && p.x < board->getWidth() && p.y >= 0 && p.y < board->getHeight();
}

PieceType GameState::getPieceType(const Position &p) const
{
    if (!isInBounds(p) || isEmpty(p))
        return PieceType::NONE;
    return board->getPieceType(p);
}

void GameState::switchPlayers()
{
    currentPlayer = PlayerColorUtils::getNext(currentPlayer);
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
            if (!checkValidState()) {
                cout << "Invalid board state, cannot exit setup" << endl;
                continue;
            }
            break;
        }
        else if (cmd == "standard")
        {
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
        }
        else if (cmd == "+")
        {
            cin >> pieceType;
            pair<PieceType, PlayerColor> p = PieceTypeUtils::fromString(pieceType);
            Position pos;
            cin >> pos;

            if (!isInBounds(pos))
            {
                cout << "Invalid position! Position: " << pos << endl;
                continue;
            }

            board->addPiece(PieceFactory::createPiece(pos, p.first, p.second, board->getWidth(), board->getHeight()), pos);
            g.updateOutputs(Move{pos, pos});
        }
        else if (cmd == "-")
        {
            Position pos;
            cin >> pos;

            if (!isInBounds(pos))
            {
                cout << "Invalid position! Position: " << pos << endl;
                continue;
            }

            if (board->popPiece(pos))
            {
                g.updateOutputs(Move{pos, pos});
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
                cout << "Invalid colour; use 'black'/'white'." << endl;
            }

            currentPlayer = PlayerColorUtils::fromString(colour);
        }
        else
        {
            cout << "Invalid command! Command: " << cmd << endl;
        }
    }
}

bool GameState::checkValidState()
{
    // no pawns on first row
    for (int x = 0; x < board->getWidth(); x++)
    {
        if (board->getPieceType({x, 0}) == PieceType::PAWN)
        {
            return false;
        }
    }

    // no pawns on last row
    for (int x = 0; x < board->getWidth(); x++)
    {
        if (board->getPieceType({x, board->getHeight()-1}) == PieceType::PAWN)
        {
            return false;
        }
    }

    int blackKingCount = 0;
    int whiteKingCount = 0;
    for (int y = 0; y < board->getHeight(); y++)
    {
        for (int x = 0; x < board->getWidth(); x++)
        {
            Position pos{x, y};
            if (board->getPieceType(pos) == PieceType::KING)
            {
                if (board->getOwner(pos) == PlayerColor::WHITE)
                {
                    whiteKingCount++;
                }
                else
                {
                    blackKingCount++;
                }
            }
        }
    }

    // both players needs exactly one king
    if (blackKingCount != 1 || whiteKingCount != 1)
    {
        return false;
    }

    // neither king can be in check
    if (isInCheck(PlayerColor::WHITE) || isInCheck(PlayerColor::BLACK))
    {
        return false;
    }

    return true;
}

// we return pair<gameIsOver, winner>
pair<bool, PlayerColor> GameState::getStatus() const
{
    vector<PlayerColor> players{PlayerColor::BLACK, PlayerColor::WHITE};

    map<PlayerColor, int> pieceCount;
    map<PlayerColor, int> kingCount;

    for (int r = 0; r < board->getHeight(); r++)
    {
        for (int c = 0; c < board->getWidth(); c++)
        {
            Position pos{r, c};
            if (!isEmpty(pos))
            {
                pieceCount[board->getOwner(pos)]++;
                if (board->getPieceType(pos) == PieceType::KING)
                {
                    kingCount[board->getOwner(pos)]++;
                }
            }
        }
    }

    // stalemate if all players have no pieces left or both have no kings left
    bool piecesLeft = false;
    bool notJustKings = false;
    for (PlayerColor pc : players)
    {
        if (pieceCount[pc] != 0)
        {
            piecesLeft = true;
        }
        if (kingCount[pc] != pieceCount[pc])
        {
            notJustKings = true;
        }
    }
    if (!piecesLeft || !notJustKings)
    {
        return make_pair(true, PlayerColor::NONE);
    }

    map<PlayerColor, int> validMoveCount;
    map<PlayerColor, bool> inCheck;
    for (PlayerColor pc : players)
    {
        validMoveCount[pc] = getValidMoves(pc).size();
        inCheck[pc] = isInCheck(pc);
    }

    // stalemate if all players are in check
    bool notAllInCheck = false;
    for (PlayerColor pc : players)
    {
        if (!inCheck[pc])
        {
            notAllInCheck = true;
        }
    }
    if (!notAllInCheck)
    {
        return make_pair(true, PlayerColor::NONE);
    }

    // stalemate if no players have valid moves
    bool notAllOutOfMoves = false;
    for (PlayerColor pc : players)
    {
        if (validMoveCount[pc] != 0)
        {
            notAllOutOfMoves = true;
        }
    }
    if (!notAllOutOfMoves)
    {
        return make_pair(true, PlayerColor::NONE);
    }

    // stalemate if a player has no valid moves and is not in check
    for (PlayerColor pc : players)
    {
        if (validMoveCount[pc] == 0 && !inCheck[pc])
        {
            return make_pair(true, PlayerColor::NONE);
        }
    }

    // checkmate if a player has no valid moves and is in check
    for (PlayerColor pc : players)
    {
        if (validMoveCount[pc] == 0 && inCheck[pc])
        {
            return make_pair(true, PlayerColorUtils::getNext(pc));
        }
    }

    return make_pair(false, PlayerColor::NONE);
}

void GameState::standard_chess_board()
{
    // Setup a standard chess board with pieces

    // Add 8 pawns to white
    for (int i = 0; i < 8; i++)
    {
        board->addPiece(PieceFactory::createPiece(Position{i, 1}, PieceType::PAWN, PlayerColor::WHITE,
                                                  board->getWidth(), board->getHeight()),
                        Position{i, 1});
    }

    // Add 8 pawns to black
    for (int i = 0; i < 8; i++)
    {
        board->addPiece(PieceFactory::createPiece(Position{i, 6}, PieceType::PAWN,
                                                  PlayerColor::BLACK, board->getWidth(), board->getHeight()),
                        Position{i, 6});
    }

    // Add 2 rooks to white
    board->addPiece(PieceFactory::createPiece(Position{0, 0}, PieceType::ROOK, PlayerColor::WHITE,
                                              board->getWidth(), board->getHeight()),
                    Position{0, 0});
    board->addPiece(PieceFactory::createPiece(Position{7, 0}, PieceType::ROOK, PlayerColor::WHITE,
                                              board->getWidth(), board->getHeight()),
                    Position{7, 0});

    // Add 2 rooks to black
    board->addPiece(PieceFactory::createPiece(Position{0, 7}, PieceType::ROOK, PlayerColor::BLACK,
                                              board->getWidth(), board->getHeight()),
                    Position{0, 7});
    board->addPiece(PieceFactory::createPiece(Position{7, 7}, PieceType::ROOK, PlayerColor::BLACK,
                                              board->getWidth(), board->getHeight()),
                    Position{7, 7});

    // Add 2 knights to white
    board->addPiece(PieceFactory::createPiece(Position{1, 0}, PieceType::KNIGHT, PlayerColor::WHITE,
                                              board->getWidth(), board->getHeight()),
                    Position{1, 0});
    board->addPiece(PieceFactory::createPiece(Position{6, 0}, PieceType::KNIGHT, PlayerColor::WHITE,
                                              board->getWidth(), board->getHeight()),
                    Position{6, 0});

    // Add 2 knights to black
    board->addPiece(PieceFactory::createPiece(Position{1, 7}, PieceType::KNIGHT, PlayerColor::BLACK,
                                              board->getWidth(), board->getHeight()),
                    Position{1, 7});
    board->addPiece(PieceFactory::createPiece(Position{6, 7}, PieceType::KNIGHT, PlayerColor::BLACK,
                                              board->getWidth(), board->getHeight()),
                    Position{6, 7});

    // Add 2 bishops to white
    board->addPiece(PieceFactory::createPiece(Position{2, 0}, PieceType::BISHOP, PlayerColor::WHITE,
                                              board->getWidth(), board->getHeight()),
                    Position{2, 0});
    board->addPiece(PieceFactory::createPiece(Position{5, 0}, PieceType::BISHOP, PlayerColor::WHITE,
                                              board->getWidth(), board->getHeight()),
                    Position{5, 0});

    // Add 2 bishops to black
    board->addPiece(PieceFactory::createPiece(Position{2, 7}, PieceType::BISHOP, PlayerColor::BLACK,
                                              board->getWidth(), board->getHeight()),
                    Position{2, 7});
    board->addPiece(PieceFactory::createPiece(Position{5, 7}, PieceType::BISHOP, PlayerColor::BLACK,
                                              board->getWidth(), board->getHeight()),
                    Position{5, 7});

    // Add 1 queen to white
    board->addPiece(PieceFactory::createPiece(Position{3, 0}, PieceType::QUEEN, PlayerColor::WHITE,
                                              board->getWidth(), board->getHeight()),
                    Position{3, 0});

    // Add 1 queen to black
    board->addPiece(PieceFactory::createPiece(Position{3, 7}, PieceType::QUEEN, PlayerColor::BLACK,
                                              board->getWidth(), board->getHeight()),
                    Position{3, 7});

    // Add 1 king to white
    board->addPiece(PieceFactory::createPiece(Position{4, 0}, PieceType::KING, PlayerColor::WHITE,
                                              board->getWidth(), board->getHeight()),
                    Position{4, 0});

    // Add 1 king to black
    board->addPiece(PieceFactory::createPiece(Position{4, 7}, PieceType::KING, PlayerColor::BLACK,
                                              board->getWidth(), board->getHeight()),
                    Position{4, 7});
}