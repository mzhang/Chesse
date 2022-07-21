#include <memory>

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

using namespace std;

unique_ptr<Moveable> PieceFactory::createPiece(const Position &p, PieceType type, PlayerColor owner, int width, int height)
{
    unique_ptr<Moveable> piece = make_unique<Piece>(p.x, p.y, type, owner);

    switch (type)
    {
        case PieceType::PAWN:
            piece = make_unique<MoveY>(std::move(piece), 1);
            break;
        case PieceType::ROOK:
            piece = make_unique<MoveX>(std::move(piece), width);
            piece = make_unique<MoveY>(std::move(piece), height);
            break;
        case PieceType::KING:
            piece = make_unique<MoveX>(std::move(piece), 1);
            piece = make_unique<MoveY>(std::move(piece), 1);
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