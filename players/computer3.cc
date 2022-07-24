#include "computer3.h"
#include "../game/gameState.h"
#include "../data/move.h"
#include "../game/board.h"

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
        if (!state.board->isEmpty(targetPos) && state.board->getOwner(targetPos) != playerColor)
        {
            return true;
        }
    }
    return false;
}

bool Computer3::isCheckingMove(const GameState &state, const Move &move)
{
    return state.checkDetection(playerColor, move, true);
}

int Computer3::isPositionAtRisk(const GameState &state, const Position &p)
{
    for (int i = 0; i < state.board->getWidth(); i++)
    {
        for (int j = 0; j < state.board->getHeight(); j++)
        {
            Position pos{i, j};
            if (!state.board->isEmpty(pos) && state.board->getOwner(pos) != playerColor)
            {
                // Get valid moves and see if any of them are to the position p
                vector<Move> validMoves = state.getValidMoves(pos);
                for (auto move : validMoves)
                {
                    // Iterate through each of the values in capturepositions and see if it is the same as p
                    for (auto to : move.capturePositions)
                    {
                        if (to == p)
                        {
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}

bool Computer3::avoidsCapture(const GameState &state, const Move &move)
{
    // Copy gamestate, make move
    GameState newState{state};

    // Count number of pieces at risk
    int num_pieces_in_check = 0;
    for (auto source : move.from)
    {
        // Check if the square at this position is threatened by any enemy piece
        if (isPositionAtRisk(newState, source))
        {
            num_pieces_in_check++;
        }
    }

    // Make move on new state
    newState.makeMove(move, isHeadless());

    // Count number of pieces at risk
    int num_pieces_in_check_after = 0;
    for (auto source : move.from)
    {
        // Check if the square at this position is threatened by any enemy piece
        if (isPositionAtRisk(newState, source))
        {
            num_pieces_in_check_after++;
        }
    }

    cout << "num_pieces_in_check: " << num_pieces_in_check << "num_pieces_in_check_after: " << num_pieces_in_check_after << endl;
    return num_pieces_in_check > num_pieces_in_check_after;
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