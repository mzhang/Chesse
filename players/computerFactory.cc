#include "computerFactory.h"
#include "player.h"
#include "computerN.h"
#include <memory>

using namespace std;

unique_ptr<Player> ComputerFactory::createComputer(PlayerColor color, int movesLookAhead)
{
    switch (color)
    {
        case PlayerColor::WHITE:
            return make_unique<ComputerN>(movesLookAhead);
        case PlayerColor::BLACK:
            return make_unique<ComputerN>(movesLookAhead);
    }
}