#ifndef COMPUTER4_H_
#define COMPUTER4_H_

#include <utility>
#include <vector>

#include "player.h"
#include "../data/move.h"

class GameState;
enum class PieceType;
enum class PlayerColor;
class Move;

class Computer4 : public Player
{
    // Piece-Square Tables to determine the value of a piece on a given square.
    // These were taken from PESTO's evaluation function (https://www.chessprogramming.org/PeSTO%27s_Evaluation_Function)

    const int pawnValues[8][8] = {{0, 0, 0, 0, 0, 0, 0, 0},
                                  {98, 134, 61, 95, 68, 126, 34, -11},
                                  {-6, 7, 26, 31, 65, 56, 25, -20},
                                  {-14, 13, 6, 21, 23, 12, 17, -23},
                                  {-27, -2, -5, 12, 17, 6, 10, -25},
                                  {-26, -4, -4, -10, 3, 3, 33, -12},
                                  {-35, -1, -20, -23, -15, 24, 38, -22},
                                  {0, 0, 0, 0, 0, 0, 0, 0}};

    const int bishopValues[8][8] = {{-29, 4, -82, -37, -25, -42, 7, -8},
                                    {-26, 16, -18, -13, 30, 59, 18, -47},
                                    {-16, 37, 43, 40, 35, 50, 37, -2},
                                    {-4, 5, 19, 50, 37, 37, 7, -2},
                                    {-6, 13, 13, 26, 34, 12, 10, 4},
                                    {0, 15, 15, 15, 14, 27, 18, 10},
                                    {4, 15, 16, 0, 7, 21, 33, 1},
                                    {-33, -3, -14, -21, -13, -12, -39, -21}};

    const int knightValues[8][8] = {{-167, -89, -34, -49, 61, -97, -15, -107},
                                    {-73, -41, 72, 36, 23, 62, 7, -17},
                                    {-47, 60, 37, 65, 84, 129, 73, 44},
                                    {-9, 17, 19, 53, 37, 69, 18, 22},
                                    {-13, 4, 16, 13, 28, 19, 21, -8},
                                    {-23, -9, 12, 10, 19, 17, 25, -16},
                                    {-29, -53, -12, -3, -1, 18, -14, -19},
                                    {-105, -21, -58, -33, -17, -28, -19, -23}};

    const int rookValues[8][8] = {{32, 42, 32, 51, 63, 9, 31, 43},
                                  {27, 32, 58, 62, 80, 67, 26, 44},
                                  {-5, 19, 26, 36, 17, 45, 61, 16},
                                  {-24, -11, 7, 26, 24, 35, -8, -20},
                                  {-36, -26, -12, -1, 9, -7, 6, -23},
                                  {-45, -25, -16, -17, 3, 0, -5, -33},
                                  {-44, -16, -20, -9, -1, 11, -6, -71},
                                  {-19, -13, 1, 17, 16, 7, -37, -26}};

    const int queenValues[8][8] = {{-28, 0, 29, 12, 59, 44, 43, 45},
                                   {-24, -39, -5, 1, -16, 57, 28, 54},
                                   {-13, -17, 7, 8, 29, 56, 47, 57},
                                   {-27, -27, -16, -16, -1, 17, -2, 1},
                                   {-9, -26, -9, -10, -2, -4, 3, -3},
                                   {-14, 2, -11, -2, -5, 2, 14, 5},
                                   {-35, -8, 11, 2, 8, 15, -3, 1},
                                   {-1, -18, -9, 10, -15, -25, -31, -50}};

    const int kingValues[8][8] = {{-65, 23, 16, -15, -56, -34, 2, 13},
                                  {29, -1, -20, -7, -8, -4, -38, -29},
                                  {-9, 24, 2, -16, -20, 6, 22, -22},
                                  {-17, -20, -12, -27, -30, -25, -14, -36},
                                  {-49, -1, -27, -39, -46, -44, -33, -51},
                                  {-14, -14, -22, -46, -44, -30, -15, -27},
                                  {1, 7, -8, -64, -43, -16, 9, 8},
                                  {-15, 36, 12, -54, 8, -28, 24, 14}};

    const int negativeInfinity = -1000000;
    const int positiveInfinity = 1000000;

    int boardCount;

    int getPieceValue(PieceType);
    std::vector<Move> orderMoves(const std::vector<Move> &);
    int getPositionValue(const Position &, PieceType);

    int evaluateMove(const GameState &, const Move &); // evaluate a specific move
    int evaluateBoard(const GameState &); // evaluate the board
    Move doNextMove(const GameState &) override;
    std::pair<int, Move> searchMoves(const GameState &, int, int, int, bool);

public:
    explicit Computer4(PlayerColor);
};

#endif // COMPUTER4_H_