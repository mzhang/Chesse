#ifndef DECORATOR_H_
#define DECORATOR_H_
#include "moveable.h"
#include <memory>

class Decorator : public Moveable
{
protected:
    std::unique_ptr<Moveable> component;

public:
    Decorator(std::unique_ptr<Moveable> component);
    virtual ~Decorator();
};

#endif
