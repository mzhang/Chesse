#include <iostream>
#include "playerColor.h"

using namespace std;

PlayerColor PlayerColorUtils::getNext(PlayerColor c)
{
    return static_cast<PlayerColor>((static_cast<int>(c) + 1) % playerNum);
}

int getInt(PlayerColor c)
{
    return static_cast<int>(c);
}

ostream &operator<<(ostream &os, const PlayerColor &c)
{
    switch (c)
    {
    case PlayerColor::WHITE:
        os << "White";
        break;
    case PlayerColor::BLACK:
        os << "Black";
        break;
    case PlayerColor::NONE:
        os << "NONE";
        break;
    }
    return os;
}

PlayerColor PlayerColorUtils::fromString(const std::string &s)
{
    if (s == "white")
    {
        return PlayerColor::WHITE;
    }
    else if (s == "black")
    {
        return PlayerColor::BLACK;
    }
    else
    {
        return PlayerColor::NONE;
    }
}