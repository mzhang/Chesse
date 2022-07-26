#ifndef GAMESTATE_H_
#define GAMESTATE_H_

#include <memory>
#include <vector>
#include <utility>
#include "../data/move.h"

class Game;
struct Position;
class Board;
enum class PlayerColor;
enum class PieceType;
class Moveable;
struct CompletedMove;

class GameState
{
    std::unique_ptr<Board> board;

public:
    PlayerColor currentPlayer;
    Move lastMove;

    GameState(int, int);
    GameState(const GameState &o);
    GameState &operator=(const GameState &o);
    void swap(GameState &o);

    ~GameState();
    void setup(const Game &);
    void standard_chess_board();
    bool checkValidState();

    bool isValidMove(const Move &m) const;
    bool isInBounds(const Position p) const;
    bool isOwner(const Position p, const PlayerColor) const;
    bool isEmpty(const Position p) const;
    int getMovedCount(const Position &p) const;
    const Moveable &getPiece(const Position &) const;

    std::vector<Move> getValidMoves(const Position &pos) const;
    std::vector<Move> getValidMoves(PlayerColor) const;

    CompletedMove makeMove(const Move &m, bool);
    void undoMove(CompletedMove &&, const Move &);

    bool isInCheck(const PlayerColor &) const;
    int numberOfTilesAttacked(const PlayerColor &, const std::vector<Position> &) const;
    bool isInCheckAfterMove(const PlayerColor &, const Move &) const;
    std::vector<Position> getEnemySightlines(const PlayerColor &) const;

    PieceType getPieceType(const Position &p) const;
    PlayerColor getOwner(const Position &p) const;

    void switchPlayers();

    std::pair<bool, PlayerColor> getStatus() const;

    friend std::istream &operator>>(std::istream &is, GameState &g);
};

#endif