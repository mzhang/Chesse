#include "computer3.h"
#include "../game/gameState.h"
#include "../data/move.h"
#include "../data/completedMove.h"
#include "../game/board.h"
#include "../data/playerColor.h"

#include <vector>
#include <random>

using namespace std;

Computer3::Computer3(PlayerColor color) : Player{color}
{
}

bool Computer3::isCapturingMove(const GameState &state, const Move &move)
{
    cout << move.capturePositions.size() << endl;
    for (auto targetPos : move.capturePositions)
    {
        if (!state.isEmpty(targetPos) && state.getOwner(targetPos) != playerColor)
        {
            return true;
        }
    }
    return false;
}

bool Computer3::isCheckingMove(const GameState &state, const Move &move)
{
    return state.isInCheckAfterMove(PlayerColorUtils::getNext(playerColor), move);
}

bool Computer3::avoidsCapture(const GameState &state, const Move &move)
{
    int attackedCount = state.numberOfTilesAttacked(playerColor, move.capturePositions);

    GameState newState{state};
    CompletedMove cm = newState.makeMove(move, isHeadless());
    int newAttackedCount = newState.numberOfTilesAttacked(playerColor, move.capturePositions);

    cout << "Number of pieces attacked before: " << attackedCount << "Number of pieces attacked after: " << newAttackedCount << endl;
    return attackedCount > newAttackedCount;
}

Move Computer3::doNextMove(const GameState &state)
{
    // Get all possible moves
    auto possible_moves = state.getValidMoves(playerColor);
    vector<Move> preferred_moves = vector<Move>();

    // Add all possible moves that are capturing moves or checking moves to preferred_moves
    for (auto move : possible_moves)
    {
        if (isCapturingMove(state, move) || isCheckingMove(state, move) || avoidsCapture(state, move))
        {
            preferred_moves.push_back(move);
        }
    }

    std::random_device rd;
    std::mt19937 generator{rd()};

    // If there are no capturing or checking moves, return a random move
    if (preferred_moves.size() == 0)
    {
        cout << "No capture avoiding, capturing or checking moves" << endl;
        std::uniform_int_distribution<int> distribution(0, possible_moves.size() - 1);
        int random_index = distribution(generator);
        return possible_moves[random_index];
    }
    else
    {
        // If there are capturing or checking moves, return a random move from the preferred moves
        std::uniform_int_distribution<int> distribution(0, preferred_moves.size() - 1);
        int random_index = distribution(generator);
        return preferred_moves[random_index];
    }
}