#include <memory>
#include <vector>

#include "pieceFactory.h"
#include "moveable.h"
#include "../data/position.h"
#include "../data/pieceType.h"
#include "../data/playerColor.h"
#include "piece.h"
#include "moveX.h"
#include "moveY.h"
#include "moveDiagPos.h"
#include "moveDiagNeg.h"
#include "moveL.h"
#include "pawnRules.h"
#include "castle.h"

using namespace std;

unique_ptr<Moveable> PieceFactory::createPiece(const Position &p, PieceType type, PlayerColor owner, int width, int height)
{
    unique_ptr<Moveable> piece = make_unique<Piece>(p.x, p.y, type, owner);

    int enpassantRow = owner == PlayerColor::WHITE ? 5 : height - 4;
    int promoteRow = owner == PlayerColor::WHITE ? height - 1 : 0;
    switch (type)
    {
    case PieceType::PAWN:
        piece = make_unique<PawnRules>(std::move(piece), enpassantRow, promoteRow, width);
        break;
    case PieceType::ROOK:
        piece = make_unique<MoveX>(std::move(piece), width);
        piece = make_unique<MoveY>(std::move(piece), height);
        break;
    case PieceType::KING:
        piece = make_unique<MoveX>(std::move(piece), 1);
        piece = make_unique<MoveY>(std::move(piece), 1);
        piece = make_unique<MoveDiagPos>(std::move(piece), 1);
        piece = make_unique<MoveDiagNeg>(std::move(piece), 1);
        piece = make_unique<Castle>(std::move(piece), vector<Position>{Position{0, p.y}, Position{width - 1, p.y}});
        break;
    case PieceType::QUEEN:
        piece = make_unique<MoveX>(std::move(piece), width);
        piece = make_unique<MoveY>(std::move(piece), height);
        piece = make_unique<MoveDiagPos>(std::move(piece), width);
        piece = make_unique<MoveDiagNeg>(std::move(piece), width);
        break;
    case PieceType::BISHOP:
        piece = make_unique<MoveDiagPos>(std::move(piece), width);
        piece = make_unique<MoveDiagNeg>(std::move(piece), width);
        break;
    case PieceType::KNIGHT:
        piece = make_unique<MoveL>(std::move(piece));
    case PieceType::NONE:
        break;
    }

    return piece;
}
