#ifndef DECORATOR_H_
#define DECORATOR_H_
#include "moveable.h"
#include <memory>

class Board;
class Position;

class Decorator : public Moveable
{
protected:
    std::unique_ptr<Moveable> component;

    virtual std::vector<Position> doGetDelta() override;
    virtual std::vector<Position> doGetValidMoves(const Board &b) override;
    virtual std::unique_ptr<Moveable> doClone() override;
    virtual void doDraw() override;

public:
    Decorator(Moveable *component);
    virtual ~Decorator() = 0;

    Decorator(const Decorator &);
};

#endif
