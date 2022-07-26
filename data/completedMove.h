#ifndef COMPLETEDMOVE_H_
#define COMPLETEDMOVE_H_

#include <vector>
#include <utility>
#include <memory>

#include "move.h"
#include "../moveable/piece.h"

// this stores all the information regarding a move that has been completed
// more specifically, it ensures that no data is lost by completing a move due to pieces being captured
// this is used to be able to revert a move
struct CompletedMove
{
    Move move;
    std::vector<std::pair<Position, std::unique_ptr<Moveable>>> capturedPieces;

    CompletedMove(const Move &, std::vector<std::pair<Position, std::unique_ptr<Moveable>>>);
    CompletedMove(CompletedMove &&);
};

#endif // COMPLETEDMOVE_H_

