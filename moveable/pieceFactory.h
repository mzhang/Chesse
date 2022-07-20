#ifndef PIECEFACTORY_H_
#define PIECEFACTORY_H_

#include <memory>

class Moveable;
struct Position;
enum class PieceType;

class PieceFactory
{
public:
    static std::unique_ptr<Moveable> createPiece(const Position &, PieceType, int, int, int);
};

#endif // PIECEFACTORY_H_