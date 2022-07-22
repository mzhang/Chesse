#ifndef GAMEHISTORY_H_
#define GAMEHISTORY_H_

#include <vector>
#include <utility>

#include "../data/move.h"
#include "../game/gameState.h"

class GameHistory {
    std::vector<std::pair<Move, GameState>> history;
public:
    explicit GameHistory(GameState state);
    void addMove(Move, GameState);
    void printHistory();
    bool empty();
    std::pair<Move, GameState> pop_back();
};

#endif