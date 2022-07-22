#include "gameHistory.h"
#include "../data/move.h"

#include <vector>

using namespace std;

void GameHistory::addMove(Move move) {
    history.push_back(move);
}

bool GameHistory::empty() {
    return history.empty();
}

Move GameHistory::lastMove() {
    return history.back();
}

void GameHistory::printHistory() {
    for (auto &move : history) {
        cout << move;
    }
}