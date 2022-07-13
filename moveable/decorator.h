#ifndef _DECORATOR_H_
#define _DECORATOR_H_
#include "moveable.h"

class Decorator : public Moveable
{
protected:
    Moveable *component;

public:
    Decorator(Moveable *component);
    virtual ~Decorator();
};

#endif
