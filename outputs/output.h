#ifndef OUTPUT_H_
#define OUTPUT_H_

#include "../game/board.h"

class Output 
{
    virtual void doUpdate(Board &b) = 0;
public:
    void update(Board &b);
};

#endif
