#ifndef GAMEHISTORY_H_
#define GAMEHISTORY_H_

#include <vector>
#include "../data/move.h"

class GameHistory {
    std::vector<Move> history;
public:
    void addMove(Move);
    void printHistory();
};

#endif