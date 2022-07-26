#ifndef PIECEFACTORY_H_
#define PIECEFACTORY_H_

#include <memory>

struct Moveable;
struct Position;
enum class PieceType;
enum class PlayerColor;

class PieceFactory {
public:
  static std::unique_ptr<Moveable> createPiece(const Position &, PieceType,
                                               PlayerColor, int, int);
};

#endif // PIECEFACTORY_H_
