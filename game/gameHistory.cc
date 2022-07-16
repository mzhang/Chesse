#include "gameHistory.h"
#include "../data/move.h"

void GameHistory::addMove(Move move) {
    history.push_back(move);
}

void GameHistory::printHistory() {
    for (auto &move : history) {
        // TODO: print this move
    }
}