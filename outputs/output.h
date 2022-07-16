#ifndef OUTPUT_H_
#define OUTPUT_H_

#include "../game/gameState.h"

class Output 
{
    virtual void doUpdate(GameState &) = 0;
public:
    void update(GameState &);
};

#endif
