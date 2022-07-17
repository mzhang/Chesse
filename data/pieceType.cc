#include "pieceType.h"
#include <string>
#include <utility>
#include <iostream>

using namespace std;

string PieceTypeUtils::toString(PieceType pieceType, int owner)
{
    switch (pieceType)
    {
        case PieceType::KING:
            return owner == 0 ? "K" : "k";
        case PieceType::QUEEN:
            return owner == 0 ? "Q" : "q";
        case PieceType::ROOK:
            return owner == 0 ? "R" : "r";
        case PieceType::BISHOP:
            return owner == 0 ? "B" : "b";
        case PieceType::KNIGHT:
            return owner == 0 ? "N" : "n";
        case PieceType::PAWN:
            return owner == 0 ? "P" : "p";
        default:
            return "";
    }
}

pair<PieceType, int> PieceTypeUtils::fromString(const string &str)
{
    if (str == "K")
        return make_pair(PieceType::KING, 0);
    else if (str == "k")
        return make_pair(PieceType::KING, 1);
    else if (str == "Q")
        return make_pair(PieceType::QUEEN, 0);
    else if (str == "q")
        return make_pair(PieceType::QUEEN, 1);
    else if (str == "R")
        return make_pair(PieceType::ROOK, 0);
    else if (str == "r")
        return make_pair(PieceType::ROOK, 1);
    else if (str == "B")
        return make_pair(PieceType::BISHOP, 0);
    else if (str == "b")
        return make_pair(PieceType::BISHOP, 1);
    else if (str == "N")
        return make_pair(PieceType::KNIGHT, 0);
    else if (str == "n")
        return make_pair(PieceType::KNIGHT, 1);
    else if (str == "P")
        return make_pair(PieceType::PAWN, 0);
    else if (str == "p")
        return make_pair(PieceType::PAWN, 1);
    
    cout << "invalid piece type, creating white pawn (should fix this btw)" << endl;
    return make_pair(PieceType::PAWN, 0);
}