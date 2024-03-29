#include "chess.h"
#include "./data/playerColor.h"
#include "./game/game.h"
#include <iostream>
#include <memory>
#include <unordered_map>
#include <utility>
using namespace std;

Chess::Chess() {
  playerScores[PlayerColor::WHITE] = 0;
  playerScores[PlayerColor::BLACK] = 0;
}
Chess::~Chess() {}

void Chess::start(bool useDisplay) {
  string cmd, player1, player2;
  while (cin >> cmd) {
    if (cmd == "game") {
      cin >> player1 >> player2;
      unordered_map<PlayerColor, string> players{{PlayerColor::WHITE, player1},
                                                 {PlayerColor::BLACK, player2}};

      Game game{boardWidth, boardHeight, useDisplay, players};
      PlayerColor winner = game.play();

      if (winner == PlayerColor::NONE) {
        for (const pair<PlayerColor, string> &player : players) {
          playerScores[player.first] += 0.5;
        }
        cout << endl;
      } else {
        cout << winner << " wins!" << endl;
        playerScores[winner] += 1;
      }
    } else {
      cout << "Invalid command! Command: " << cmd << endl;
    }
  }

  // print game results
  cout << "Final Score:" << endl;
  cout << "White: " << playerScores[PlayerColor::WHITE] << endl;
  cout << "Black: " << playerScores[PlayerColor::BLACK] << endl;
}
