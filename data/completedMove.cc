#include <memory>
#include <vector>

#include "../moveable/moveable.h"
#include "completedMove.h"
#include "move.h"

using namespace std;

CompletedMove::CompletedMove(
    const Move &move,
    vector<pair<Position, unique_ptr<Moveable>>> capturedPieces)
    : move{move}, capturedPieces{std::move(capturedPieces)} {}

CompletedMove::CompletedMove(CompletedMove &&o)
    : move{std::move(o.move)}, capturedPieces{std::move(o.capturedPieces)} {}
