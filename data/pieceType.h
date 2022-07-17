#ifndef PIECE_TYPE_H_
#define PIECE_TYPE_H_

#include <string>
#include <utility>

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
    static std::string toString(PieceType pieceType, int owner); // used for deciding what image to display
    static std::pair<PieceType, int> fromString(const std::string &str);
};

#endif