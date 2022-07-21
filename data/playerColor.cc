#include "playerColor.h"

PlayerColor PlayerColorUtils::getNext(PlayerColor c)
{
    return static_cast<PlayerColor>((static_cast<int>(c) + 1) % playerNum);
}

int getInt(PlayerColor c)
{
    return static_cast<int>(c);
}