#include "pieceType.h"
#include "playerColor.h"
#include <iostream>
#include <string>
#include <utility>

using namespace std;

string PieceTypeUtils::toString(PieceType pieceType, PlayerColor owner) {
  switch (pieceType) {
  case PieceType::KING:
    return owner == PlayerColor::WHITE ? "K" : "k";
  case PieceType::QUEEN:
    return owner == PlayerColor::WHITE ? "Q" : "q";
  case PieceType::ROOK:
    return owner == PlayerColor::WHITE ? "R" : "r";
  case PieceType::BISHOP:
    return owner == PlayerColor::WHITE ? "B" : "b";
  case PieceType::KNIGHT:
    return owner == PlayerColor::WHITE ? "N" : "n";
  case PieceType::PAWN:
    return owner == PlayerColor::WHITE ? "P" : "p";
  default:
    return "";
  }
}

pair<PieceType, PlayerColor> PieceTypeUtils::fromString(const string &str) {
  if (str == "K")
    return make_pair(PieceType::KING, PlayerColor::WHITE);
  else if (str == "k")
    return make_pair(PieceType::KING, PlayerColor::BLACK);
  else if (str == "Q")
    return make_pair(PieceType::QUEEN, PlayerColor::WHITE);
  else if (str == "q")
    return make_pair(PieceType::QUEEN, PlayerColor::BLACK);
  else if (str == "R")
    return make_pair(PieceType::ROOK, PlayerColor::WHITE);
  else if (str == "r")
    return make_pair(PieceType::ROOK, PlayerColor::BLACK);
  else if (str == "B")
    return make_pair(PieceType::BISHOP, PlayerColor::WHITE);
  else if (str == "b")
    return make_pair(PieceType::BISHOP, PlayerColor::BLACK);
  else if (str == "N")
    return make_pair(PieceType::KNIGHT, PlayerColor::WHITE);
  else if (str == "n")
    return make_pair(PieceType::KNIGHT, PlayerColor::BLACK);
  else if (str == "P")
    return make_pair(PieceType::PAWN, PlayerColor::WHITE);
  else if (str == "p")
    return make_pair(PieceType::PAWN, PlayerColor::BLACK);

  cout << "Invalid piece type! Input: " << str << endl;
  return make_pair(PieceType::NONE, PlayerColor::NONE);
}
