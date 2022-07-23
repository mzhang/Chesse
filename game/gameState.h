#ifndef GAMESTATE_H_
#define GAMESTATE_H_

#include <memory>
#include <vector>

class Game;
struct Position;
class Board;
struct Move;
enum class PlayerColor;

class GameState
{
public:
    std::unique_ptr<Board> board;
    PlayerColor currentPlayer; // white = 0; black = 1

    GameState(int, int);
    GameState(const GameState &o);
    GameState &operator=(const GameState &o);
    void swap(GameState &o);

    ~GameState();
    void setup(const Game &);
    void standard_chess_board();

    bool isValidMove(const Move &m) const;
    bool isInBounds(const Position p) const;
    bool isOwner(const Position p, const PlayerColor) const;
    bool isEmpty(const Position p) const;
    std::vector<Move> getValidMoves(const Position &pos) const;
    std::vector<Move> getValidMoves(PlayerColor) const;
    void makeMove(const Move &m);
    bool checkDetection(PlayerColor, Move, bool=false) const;

    void switchPlayers();

    friend std::istream &operator>>(std::istream &is, GameState &g);
};

#endif