#include "gameHistory.h"
#include "../data/move.h"

#include <utility>

using namespace std;

GameHistory::GameHistory(GameState state)
{
    history.push_back(make_pair(Move(), state));
}

void GameHistory::addMove(Move move, GameState state) {
    history.push_back(make_pair(move, state));
}

void GameHistory::printHistory() {
    // Print every move in the history
    for (auto move : history) {
        cout << move.first << endl;
    }
}

bool GameHistory::empty() {
    return history.empty();
}

pair<Move, GameState> GameHistory::pop_back() {
    // Pop the last move off the history
    auto last = history.back();
    history.pop_back();
    return last;
}