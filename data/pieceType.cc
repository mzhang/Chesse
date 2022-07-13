#include "pieceType.h"
#include <string>

using namespace std;

string PieceTypeUtils::toString(PieceType pieceType)
{
    switch (pieceType)
    {
    case PieceType::KING:
        return "King";
    case PieceType::QUEEN:
        return "Queen";
    case PieceType::ROOK:
        return "Rook";
    case PieceType::BISHOP:
        return "Bishop";
    case PieceType::KNIGHT:
        return "Knight";
    case PieceType::PAWN:
        return "Pawn";
    default:
        return "";
    }
}