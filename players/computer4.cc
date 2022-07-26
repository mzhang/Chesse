#include <random>
#include <iostream>
#include <utility>
#include <algorithm>

#include "computer4.h"
#include "../game/gameState.h"
#include "../data/move.h"
#include "../game/board.h"
#include "../data/playerColor.h"
#include "../data/completedMove.h"

using namespace std;

Computer4::Computer4(PlayerColor color) : Player{color}
{
}

Move Computer4::doNextMove(const GameState &g)
{
    GameState newState{g};
    int searchDepth = 4;

    boardCount = 0;
    pair<float, Move> evaluation = searchMoves(newState, searchDepth, negativeInfinity, positiveInfinity, true);

    // cout << "Evaluated " << boardCount << " boards" << endl;
    // cout << "Best evaluation: " << evaluation.first << endl;

    return evaluation.second;
}

// Use alpha-beta pruning to find the best move
// Algorithm is based on pseudocode from Wikipedia (https://en.wikipedia.org/wiki/Alpha–beta_pruning)
pair<int, Move> Computer4::searchMoves(GameState &g, int depth, int alpha, int beta, bool maximizingPlayer)
{
    if (depth == 0) {
        //cout << "Depth 0: " << evaluateBoard(g) << endl;
        return make_pair(evaluateBoard(g), Move{});
    }
     
    // We order the moves to improve amount of branches pruned
    vector<Move> validMoves = orderMoves(g.getValidMoves(g.currentPlayer)); // TODO: order moves

    if (validMoves.size() == 0) {
        //cout << "ValidMoves 0: " << evaluateBoard(g) << endl;
        return make_pair(evaluateBoard(g), Move{});
    }

    if (maximizingPlayer) {
        int value = negativeInfinity;
        Move bestMove;

        for (auto &move : validMoves) {
            auto lastMove = g.lastMove;
            auto c = g.makeMove(move, true);
            g.switchPlayers();
            auto evaluation = searchMoves(g, depth - 1, alpha, beta, false);
            g.undoMove(std::move(c), lastMove);
            if (evaluation.first > value) {
                value = evaluation.first;
                bestMove = move;
            }

            alpha = max(alpha, value);
            if (value >= beta)
                break;
        }
        return make_pair(value, bestMove);
    } else {
        int value = positiveInfinity;
        Move bestMove;

        for (auto &move : validMoves) {
            GameState newState = g;
            newState.makeMove(move, true);
            newState.switchPlayers();
            auto evaluation = searchMoves(newState, depth - 1, alpha, beta, true);
            //cout << "Evaluation: " << evaluation.first << endl;
            if (evaluation.first < value) {
                value = evaluation.first;
                bestMove = move;
            }

            beta = min(beta, value);
            if (value <= alpha)
                break;
        }
        return make_pair(value, bestMove);
    }
}

// TODO: improve
vector<Move> Computer4::orderMoves(const vector<Move> &moves)
{
    vector<Move> orderedMoves;
    for (auto move : moves)
    {
        if (move.capturePositions.size() > 0)
        {
            orderedMoves.push_back(move);
        }
    }
    for (auto move : moves)
    {
        if (move.capturePositions.size() == 0)
        {
            orderedMoves.push_back(move);
        }
    }
    return orderedMoves;
}

int Computer4::evaluateBoard(const GameState &g)
{
    int evaluation = 0;

    pair<bool, PlayerColor> gameEnded = g.getStatus();
    if (gameEnded.first) {
        if (gameEnded.second == PlayerColor::NONE) {
            return 0;
        }
        else {
            return gameEnded.second == playerColor ? positiveInfinity / 10 : negativeInfinity / 10;
        }
    }

    if (g.isInCheck(playerColor)) { // not in checkmate, but in check
        evaluation -= 50;
    }

    for (int y = 0; y < 8; y++)
    {
        for (int x = 0; x < 8; x++)
        {
            Position pos{x, y};
            PieceType pieceType = g.getPieceType(pos);
            int positionValue = getPositionValue(pos, pieceType);
            int pieceValue = getPieceValue(pieceType);
            evaluation += g.isOwner(pos, playerColor) ? pieceValue : -pieceValue;
            evaluation += g.isOwner(pos, playerColor) ? positionValue : -positionValue;
        }
    }

    return evaluation;
}

int Computer4::getPieceValue(PieceType pieceType)
{
    switch (pieceType)
    {
    case PieceType::KING:
        return 100000;
    case PieceType::QUEEN:
        return 900;
    case PieceType::ROOK:
        return 500;
    case PieceType::BISHOP:
        return 300;
    case PieceType::KNIGHT:
        return 300;
    case PieceType::PAWN:
        return 100;
    default:
        return 0;
    }
}

int Computer4::getPositionValue(const Position &pos, PieceType pieceType)
{
    const float positionWeight = 0.5f;
    int yPos = playerColor == PlayerColor::WHITE ? pos.y : 7 - pos.y;
    int xPos = pos.x;

    switch (pieceType)
    {
        case PieceType::PAWN:
            return pawnValues[yPos][xPos] * positionWeight;
        case PieceType::BISHOP:
            return bishopValues[yPos][xPos] * positionWeight;
        case PieceType::KNIGHT:
            return knightValues[yPos][xPos] * positionWeight;
        case PieceType::ROOK:
            return rookValues[yPos][xPos] * positionWeight;
        case PieceType::QUEEN:
            return queenValues[yPos][xPos] * positionWeight;
        case PieceType::KING:
            return kingValues[yPos][xPos] * positionWeight;
        default:
            return 0;
    }
}