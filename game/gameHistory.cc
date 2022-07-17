#include "gameHistory.h"
#include "../data/move.h"

using namespace std;

void GameHistory::addMove(Move move) {
    history.push_back(move);
}

void GameHistory::printHistory() {
    for (auto &move : history) {
        cout << move;
    }
}