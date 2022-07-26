#ifndef COMPUTER_FACTORY_H_
#define COMPUTER_FACTORY_H_

#include "player.h"
#include <memory>

enum class PlayerColor;

class ComputerFactory {
public:
  static std::unique_ptr<Player> createComputer(PlayerColor color,
                                                int movesLookAhead);
};

#endif // COMPUTER_FACTORY_H_
