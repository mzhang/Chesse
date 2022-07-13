#ifndef DECORATOR_H_
#define DECORATOR_H_
#include "moveable.h"
#include <memory>

class Decorator : public Moveable
{
protected:
    std::unique_ptr<Moveable> component;

public:
    Decorator(Moveable *component);
    virtual ~Decorator() = 0;

    Decorator(const Decorator &);
};

#endif
