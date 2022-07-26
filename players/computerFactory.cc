#include "computerFactory.h"
#include "player.h"
#include "computerN.h"
#include <memory>

using namespace std;

unique_ptr<Player> ComputerFactory::createComputer(PlayerColor color, int movesLookAhead)
{
    return make_unique<ComputerN>(color, movesLookAhead);
}