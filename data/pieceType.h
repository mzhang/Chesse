#ifndef PIECE_TYPE_H_
#define PIECE_TYPE_H_

#include <string>

enum class PieceType
{
    KING,
    QUEEN,
    ROOK,
    BISHOP,
    KNIGHT,
    PAWN
};

class PieceTypeUtils
{
public:
    static std::string toString(PieceType pieceType);
}


#endif