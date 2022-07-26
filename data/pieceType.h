#ifndef PIECE_TYPE_H_
#define PIECE_TYPE_H_

#include <string>
#include <utility>

enum class PlayerColor;
enum class PieceType
{
    KING,
    QUEEN,
    ROOK,
    BISHOP,
    KNIGHT,
    PAWN,
    NONE
};

class PieceTypeUtils
{
public:
    static std::string toString(PieceType pieceType, PlayerColor owner); // used for deciding what image to display
    static std::pair<PieceType, PlayerColor> fromString(const std::string &str);
};

#endif
