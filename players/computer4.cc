#include <random>
#include <iostream>
#include <utility>
#include <algorithm>

#include "computer4.h"
#include "../game/gameState.h"
#include "../data/move.h"
#include "../game/board.h"
#include "../data/playerColor.h"

using namespace std;

Computer4::Computer4(PlayerColor color) : Player{color}
{
}

Move Computer4::doNextMove(const GameState &g)
{
    int searchDepth = 4;

    boardCount = 0;
    pair<float, Move> evaluation = searchMoves(g, searchDepth, evaluateBoard(g), negativeInfinity, positiveInfinity, true);

    cout << "Evaluated " << boardCount << " boards" << endl;
    cout << "Best evaluation: " << evaluation.first << endl;

    return evaluation.second;
}

// Use alpha-beta pruning to find the best move
// Algorithm is based on pseudocode from Wikipedia (https://en.wikipedia.org/wiki/Alpha–beta_pruning)
// Additionally, we pass in the evaluation for the current board state. This lets evaluate moves instead of board states
// This also avoids having to deal with invalid board states 
pair<int, Move> Computer4::searchMoves(const GameState &g, int depth, int currentEval, int alpha, int beta, bool maximizingPlayer)
{
    if (depth == 0)
        return make_pair(currentEval, Move{});

    // We order the moves to improve amount of branches pruned
    vector<Move> validMoves = orderMoves(g.getValidMoves(g.currentPlayer));

    if (validMoves.size() == 0)
        return make_pair(currentEval, Move{});

    Move currentBestMove;
    int currentBestScore = maximizingPlayer ? negativeInfinity : positiveInfinity;

    for (auto move : validMoves)
    {
        GameState newState = g;
        boardCount++;

        int updatedEval = currentEval + evaluateMove(newState, move);
        newState.makeMove(move, isHeadless());
        pair<float, Move> evaluation = searchMoves(newState, depth - 1, updatedEval, alpha, beta, !maximizingPlayer);

        if (maximizingPlayer)
        {
            if (evaluation.first >= currentBestScore)
            {
                currentBestScore = evaluation.first;
                currentBestMove = move;
            }
            
            alpha = max(alpha, currentBestScore);
            if (currentBestScore >= beta)
                break;
        }
        else
        {
            if (evaluation.first < currentBestScore)
            {
                currentBestScore = evaluation.first;
                currentBestMove = move;
            }
            beta = min(beta, currentBestScore);

            if (currentBestScore < alpha) break;
        }
    }

    return make_pair(currentBestScore, currentBestMove);
}

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

    // TODO: check if king is in check

    for (int y = 0; y < 8; y++)
    {
        for (int x = 0; x < 8; x++)
        {
            Position pos{x, y};
            PieceType pieceType = g.getPieceType(pos);
            int positionValue = getPositionValue(pos, pieceType);
            evaluation += g.isOwner(pos, playerColor) ? positionValue : -positionValue;
        }
    }

    return evaluation;
}

int Computer4::evaluateMove(const GameState &g, const Move &m)
{
    int evaluation = 0;

    // TODO: checkmate/stalemate/etc.

    for (auto pos : m.capturePositions)
    {
        PieceType capturedPiece = g.getPieceType(pos);
        int pieceValue = getPieceValue(capturedPiece) + getPositionValue(pos, capturedPiece);
        evaluation += !g.isOwner(pos, playerColor) ? pieceValue : -pieceValue;
    }

    // TODO: promotion

    for (int i = 0; i < (int)m.from.size(); ++i)
    {
        PieceType pieceType = g.getPieceType(m.from[i]);
        int newPositionValue = getPositionValue(m.to[i], pieceType) - getPositionValue(m.from[i], pieceType);
        evaluation += g.isOwner(m.from[i], playerColor) ? newPositionValue : -newPositionValue;
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