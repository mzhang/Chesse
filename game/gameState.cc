#include <algorithm>
#include <iostream>
#include <map>
#include <memory>
#include <utility>
#include <vector>

#include "../data/completedMove.h"
#include "../data/pieceType.h"
#include "../data/playerColor.h"
#include "../data/position.h"
#include "../moveable/moveable.h"
#include "../moveable/pieceFactory.h"
#include "board.h"
#include "game.h"
#include "gameState.h"

#include "../outputs/textDisplay.h"

#include "../moveable/brick.h"
#include "../moveable/castle.h"
#include "../moveable/checker.h"
#include "../moveable/golem.h"
#include "../moveable/moveDiagNeg.h"
#include "../moveable/moveDiagPos.h"
#include "../moveable/moveL.h"
#include "../moveable/moveX.h"
#include "../moveable/moveY.h"
#include "../moveable/nuke.h"
#include "../moveable/pawnRules.h"

#include <util.h>

using namespace std;

GameState::GameState(int boardWidth, int boardHeight)
    : board{make_unique<Board>(boardWidth, boardHeight)},
      currentPlayer{PlayerColor::WHITE} {}

GameState::GameState(const GameState &o)
    : board{make_unique<Board>(*o.board)}, currentPlayer{o.currentPlayer} {
  /*cout << "DEBUG: GameState copy constructor. Make sure this is intended" <<
   * endl;*/
}

GameState::~GameState() {}

void GameState::swap(GameState &o) {
  std::swap(board, o.board);
  std::swap(currentPlayer, o.currentPlayer);
}

GameState &GameState::operator=(const GameState &o) {
  GameState tmp{o};
  swap(tmp);
  return *this;
}

bool GameState::isValidMove(const Move &m) const {
  // pre: m is not malformed
  Position mainPos = m.from[0];
  if (!isInBounds(mainPos) || isEmpty(mainPos)) {
    return false;
  }

  const Moveable &piece = board->getPiece(mainPos);
  vector<Move> validMoves = piece.getValidMoves(*this);
  return std::find(validMoves.begin(), validMoves.end(), m) !=
             validMoves.end() &&
         !isInCheckAfterMove(piece.getOwner(), m);
}

// Precondition: move accounts for all side effects
CompletedMove GameState::makeMove(const Move &m, bool headless) {
  lastMove = m;
  return board->makeMove(m, headless);
}

void GameState::undoMove(CompletedMove &&m, const Move &previousMove) {
  board->undoMove(std::move(m));
  lastMove = previousMove;
}

bool GameState::isInCheck(const PlayerColor &pc) const {
  vector<Position> kingPos{};
  for (int i = 0; i < board->getWidth(); i++) {
    for (int j = 0; j < board->getHeight(); j++) {
      Position pos{i, j};
      if (!isEmpty(pos) && getPieceType(pos) == PieceType::KING &&
          isOwner(pos, pc)) {
        kingPos.emplace_back(pos);
      }
    }
  }
  return numberOfTilesAttacked(pc, kingPos) > 0;
}

// getEnemySightlines is expensive so we pass in vector to minimize calls
int GameState::numberOfTilesAttacked(const PlayerColor &pc,
                                     const vector<Position> &positions) const {
  int numAttacked = 0;
  vector<Position> enemySightlines = getEnemySightlines(pc);
  for (const Position &pos : positions) {
    if (std::find(enemySightlines.begin(), enemySightlines.end(), pos) !=
        enemySightlines.end()) {
      ++numAttacked;
    }
  }
  return numAttacked;
}

bool GameState::isInCheckAfterMove(const PlayerColor &pc, const Move &m) const {
  CompletedMove cm = board->makeMove(m, true);
  bool inCheck = isInCheck(pc);
  board->undoMove(std::move(cm));
  return inCheck;
}

vector<Position> GameState::getEnemySightlines(const PlayerColor &pc) const {
  vector<Position> sightline;
  for (int r = 0; r < board->getHeight(); r++) {
    for (int c = 0; c < board->getWidth(); c++) {
      Position pos{r, c};
      if (!isEmpty(pos) && !isOwner(pos, pc)) {
        vector<Position> attackedTiles =
            board->getPiece(pos).getAttackedTiles(*this);
        sightline.insert(sightline.end(), attackedTiles.begin(),
                         attackedTiles.end());
      }
    }
  }
  return sightline;
}

vector<Move> GameState::getValidMoves(const Position &pos) const {
  if (isEmpty(pos)) {
    return vector<Move>{};
  }

  const Moveable &piece = board->getPiece(pos);

  vector<Move> validMoves;
  vector<Move> pieceSightlines = piece.getValidMoves(*this);

  for (auto &move : pieceSightlines) {
    if (!isInCheckAfterMove(board->getOwner(pos), move)) {
      validMoves.push_back(move);
    }
  }

  return validMoves;
}

vector<Move> GameState::getValidMoves(PlayerColor pc) const {
  vector<Move> validMoves;
  for (int i = 0; i < board->getWidth(); i++) {
    for (int j = 0; j < board->getHeight(); j++) {
      Position pos{i, j};
      if (!isEmpty(pos) && isOwner(pos, pc)) {
        vector<Move> pieceValidMoves = getValidMoves(pos);
        validMoves.insert(validMoves.end(), pieceValidMoves.begin(),
                          pieceValidMoves.end());
      }
    }
  }
  return validMoves;
}

int GameState::getMovedCount(const Position &pos) const {
  if (!isInBounds(pos) || isEmpty(pos)) {
    return 0;
  }
  return board->getMovedCount(pos);
}

bool GameState::isOwner(const Position p, const PlayerColor playerColor) const {
  if (!isInBounds(p) || isEmpty(p))
    return false;
  return board->getOwner(p) == playerColor;
}

PlayerColor GameState::getOwner(const Position &p) const {
  if (!isInBounds(p) || isEmpty(p))
    return PlayerColor::NONE;
  return board->getOwner(p);
}

bool GameState::isEmpty(const Position p) const { return board->isEmpty(p); }

bool GameState::isInBounds(const Position p) const {
  return p.x >= 0 && p.x < board->getWidth() && p.y >= 0 &&
         p.y < board->getHeight();
}

PieceType GameState::getPieceType(const Position &p) const {
  if (!isInBounds(p) || isEmpty(p))
    return PieceType::NONE;
  return board->getPieceType(p);
}

void GameState::switchPlayers() {
  currentPlayer = PlayerColorUtils::getNext(currentPlayer);
}

void GameState::switchPlayersBack() {
  currentPlayer = PlayerColorUtils::getPrevious(currentPlayer);
}

void GameState::setup(const Game &g) {
  string cmd;
  string pieceType;
  string colour;

  while (cin >> cmd) {
    if (cmd == "done") {
      if (!checkValidState()) {
        cout << "Invalid board state, cannot exit setup" << endl;
        continue;
      }
      break;
    } else if (cmd == "standard") {
      standard_chess_board();
      Move m;
      // Add the bottom and top two rows to m.from
      for (int i = 0; i < board->getWidth(); i++) {
        m.from.push_back({i, 0});
        m.from.push_back({i, 1});
        m.from.push_back({i, board->getHeight() - 1});
        m.from.push_back({i, board->getHeight() - 2});
      }
      g.updateOutputs(m);
    } else if (cmd == "checkers") {
      standard_checkers_board();
      Move m;
      // Add the bottom 3 rows and the top 3 rows to m.from
      for (int i = 0; i < board->getWidth(); i++) {
        m.from.push_back({i, 0});
        m.from.push_back({i, 1});
        m.from.push_back({i, 2});
        m.from.push_back({i, board->getHeight() - 1});
        m.from.push_back({i, board->getHeight() - 2});
        m.from.push_back({i, board->getHeight() - 3});
      }
      m.from.push_back({3, 4});
      m.from.push_back({4, 3});
      g.updateOutputs(m);
    } else if (cmd == "+") {
      cin >> pieceType;
      pair<PieceType, PlayerColor> p = PieceTypeUtils::fromString(pieceType);
      Position pos;
      cin >> pos;

      if (!isInBounds(pos)) {
        cout << "Invalid position! Position: " << pos << endl;
        continue;
      }

      board->addPiece(PieceFactory::createPiece(pos, p.first, p.second,
                                                board->getWidth(),
                                                board->getHeight()),
                      pos);
      g.updateOutputs(Move{pos, pos});
    } else if (cmd == "-") {
      Position pos;
      cin >> pos;

      if (!isInBounds(pos)) {
        cout << "Invalid position! Position: " << pos << endl;
        continue;
      }

      if (board->popPiece(pos)) {
        g.updateOutputs(Move{pos, pos});
      }
    } else if (cmd == "*") {
      // re-decorate a piece with a new rule
      string newRule;
      cin >> newRule;
      Position pos;
      cin >> pos;
      if (!isInBounds(pos)) {
        cout << "Invalid position! Position: " << pos << endl;
        continue;
      }
      if (isEmpty(pos)) {
        cout << "Position is empty! Position: " << pos << endl;
        continue;
      }
      unique_ptr<Moveable> piece = board->popPiece(pos);
      int width = board->getWidth();
      int height = board->getHeight();
      PlayerColor owner = piece->getOwner();
      if (newRule == "moveX") {
        int maxSteps;
        cout << "What is the maximum range for the piece at " << pos << "?"
             << endl;
        cin >> maxSteps;
        board->addPiece(make_unique<MoveX>(std::move(piece), maxSteps), pos);
      } else if (newRule == "moveY") {
        int maxSteps;
        cout << "What is the maximum range for the piece at " << pos << "?"
             << endl;
        cin >> maxSteps;
        board->addPiece(make_unique<MoveY>(std::move(piece), maxSteps), pos);
      } else if (newRule == "moveDiagNeg") {
        int maxSteps;
        cout << "What is the maximum range for the piece at " << pos << "?"
             << endl;
        cin >> maxSteps;
        board->addPiece(make_unique<MoveDiagNeg>(std::move(piece), maxSteps),
                        pos);
      } else if (newRule == "moveDiagPos") {
        int maxSteps;
        cout << "What is the maximum range for the piece at " << pos << "?"
             << endl;
        cin >> maxSteps;
        board->addPiece(make_unique<MoveDiagPos>(std::move(piece), maxSteps),
                        pos);
      } else if (newRule == "moveL") {
        board->addPiece(make_unique<MoveL>(std::move(piece)), pos);
      } else if (newRule == "pawnRules") {
        int enpassantRow = owner == PlayerColor::WHITE ? 5 : height - 4;
        int promoteRow = owner == PlayerColor::WHITE ? height - 1 : 0;
        board->addPiece(make_unique<PawnRules>(std::move(piece), enpassantRow,
                                               promoteRow, width),
                        pos);
      } else if (newRule == "castle") {
        vector<Position> partners{Position{0, pos.y},
                                  Position{width - 1, pos.y}};
        board->addPiece(make_unique<Castle>(std::move(piece), partners), pos);
      } else if (newRule == "golem") {
        int maxSteps;
        cout << "What is the maximum range for the piece at " << pos << "?"
             << endl;
        cin >> maxSteps;
        board->addPiece(make_unique<Golem>(std::move(piece), maxSteps), pos);
      } else if (newRule == "nuke") {
        board->addPiece(make_unique<Nuke>(std::move(piece)), pos);
      } else if (newRule == "brick") {
        board->addPiece(make_unique<Brick>(std::move(piece)), pos);
      } else if (newRule == "checker") {
        int promoteRow = owner == PlayerColor::WHITE ? height - 1 : 0;
        board->addPiece(make_unique<Checker>(std::move(piece), promoteRow),
                        pos);
      } else {
        cout << "Invalid rule! Rule: " << newRule << endl;
        continue;
      }

      g.updateOutputs(Move{pos, pos});
    } else if (cmd == "=") {
      while (cin >> colour) {
        if (colour == "black" || colour == "white") {
          break;
        }
        cout << "Invalid colour; use 'black'/'white'." << endl;
      }

      currentPlayer = PlayerColorUtils::fromString(colour);
    } else {
      cout << "Invalid command! Command: " << cmd << endl;
    }
  }
}

bool GameState::checkValidState() {
  // no pawns on first row
  for (int x = 0; x < board->getWidth(); x++) {
    if (board->getPieceType({x, 0}) == PieceType::PAWN) {
      return false;
    }
  }

  // no pawns on last row
  for (int x = 0; x < board->getWidth(); x++) {
    if (board->getPieceType({x, board->getHeight() - 1}) == PieceType::PAWN) {
      return false;
    }
  }

  int blackKingCount = 0;
  int whiteKingCount = 0;
  for (int y = 0; y < board->getHeight(); y++) {
    for (int x = 0; x < board->getWidth(); x++) {
      Position pos{x, y};
      if (board->getPieceType(pos) == PieceType::KING) {
        if (board->getOwner(pos) == PlayerColor::WHITE) {
          whiteKingCount++;
        } else {
          blackKingCount++;
        }
      }
    }
  }

  // both players needs exactly one king
  if (blackKingCount != 1 || whiteKingCount != 1) {
    return false;
  }

  // neither king can be in check
  if (isInCheck(PlayerColor::WHITE) || isInCheck(PlayerColor::BLACK)) {
    return false;
  }

  return true;
}

// we return pair<gameIsOver, winner>
pair<bool, PlayerColor> GameState::getStatus() const {

  // Efficiently determine if the game is over and the winner if so
  // We do this by checking if there are any valid moves for both players
  // If there are no valid moves for both players, then the game is over

  // if (getValidMoves(PlayerColor::WHITE).size() == 0 &&
  // getValidMoves(PlayerColor::BLACK).size() == 0)
  // {
  //     // Return the winner by check
  //     return make_pair(true, PlayerColor::NONE);
  // }

  vector<PlayerColor> players{PlayerColor::BLACK, PlayerColor::WHITE};

  map<PlayerColor, int> pieceCount;
  map<PlayerColor, int> kingCount;

  for (int r = 0; r < board->getHeight(); r++) {
    for (int c = 0; c < board->getWidth(); c++) {
      Position pos{r, c};
      if (!isEmpty(pos)) {
        pieceCount[board->getOwner(pos)]++;
        if (board->getPieceType(pos) == PieceType::KING) {
          kingCount[board->getOwner(pos)]++;
        }
      }
    }
  }

  // stalemate if all players have no pieces left or both have no kings left
  bool piecesLeft = false;
  bool notJustKings = false;
  for (PlayerColor pc : players) {
    if (pieceCount[pc] != 0) {
      piecesLeft = true;
    }
    if (kingCount[pc] != 0) {
      notJustKings = true;
    }
  }
  if (!piecesLeft || !notJustKings) {
    return make_pair(true, PlayerColor::NONE);
  }

  // player wins if they have a king and the other doesn't
  // player wins if they have pieces and the other doesn't
  for (PlayerColor pc : players) {
    if ((kingCount[pc] > 0 && kingCount[PlayerColorUtils::getNext(pc)] == 0) ||
        (pieceCount[pc] > 0 &&
         pieceCount[PlayerColorUtils::getNext(pc)] == 0)) {
      return make_pair(true, pc);
    }
  }

  map<PlayerColor, int> validMoveCount;
  map<PlayerColor, bool> inCheck;
  for (PlayerColor pc : players) {
    validMoveCount[pc] = getValidMoves(pc).size();
    inCheck[pc] = isInCheck(pc);
  }

  // stalemate if all players are in check
  bool notAllInCheck = false;
  for (PlayerColor pc : players) {
    if (!inCheck[pc]) {
      notAllInCheck = true;
    }
  }
  if (!notAllInCheck) {
    return make_pair(true, PlayerColor::NONE);
  }

  // stalemate if no players have valid moves
  bool notAllOutOfMoves = false;
  for (PlayerColor pc : players) {
    if (validMoveCount[pc] != 0) {
      notAllOutOfMoves = true;
    }
  }
  if (!notAllOutOfMoves) {
    return make_pair(true, PlayerColor::NONE);
  }

  // stalemate if a player has no valid moves and is not in check
  for (PlayerColor pc : players) {
    if (validMoveCount[pc] == 0 && !inCheck[pc]) {
      return make_pair(true, PlayerColor::NONE);
    }
  }

  // checkmate if a player has no valid moves and is in check
  for (PlayerColor pc : players) {
    if (validMoveCount[pc] == 0 && inCheck[pc]) {
      return make_pair(true, PlayerColorUtils::getNext(pc));
    }
  }

  return make_pair(false, PlayerColor::NONE);
}

void GameState::standard_chess_board() {
  // Setup a standard chess board with pieces

  // Add 8 pawns to white
  for (int i = 0; i < 8; i++) {
    board->addPiece(PieceFactory::createPiece(
                        Position{i, 1}, PieceType::PAWN, PlayerColor::WHITE,
                        board->getWidth(), board->getHeight()),
                    Position{i, 1});
  }

  // Add 8 pawns to black
  for (int i = 0; i < 8; i++) {
    board->addPiece(PieceFactory::createPiece(
                        Position{i, 6}, PieceType::PAWN, PlayerColor::BLACK,
                        board->getWidth(), board->getHeight()),
                    Position{i, 6});
  }

  // Add 2 rooks to white
  board->addPiece(PieceFactory::createPiece(
                      Position{0, 0}, PieceType::ROOK, PlayerColor::WHITE,
                      board->getWidth(), board->getHeight()),
                  Position{0, 0});
  board->addPiece(PieceFactory::createPiece(
                      Position{7, 0}, PieceType::ROOK, PlayerColor::WHITE,
                      board->getWidth(), board->getHeight()),
                  Position{7, 0});

  // Add 2 rooks to black
  board->addPiece(PieceFactory::createPiece(
                      Position{0, 7}, PieceType::ROOK, PlayerColor::BLACK,
                      board->getWidth(), board->getHeight()),
                  Position{0, 7});
  board->addPiece(PieceFactory::createPiece(
                      Position{7, 7}, PieceType::ROOK, PlayerColor::BLACK,
                      board->getWidth(), board->getHeight()),
                  Position{7, 7});

  // Add 2 knights to white
  board->addPiece(PieceFactory::createPiece(
                      Position{1, 0}, PieceType::KNIGHT, PlayerColor::WHITE,
                      board->getWidth(), board->getHeight()),
                  Position{1, 0});
  board->addPiece(PieceFactory::createPiece(
                      Position{6, 0}, PieceType::KNIGHT, PlayerColor::WHITE,
                      board->getWidth(), board->getHeight()),
                  Position{6, 0});

  // Add 2 knights to black
  board->addPiece(PieceFactory::createPiece(
                      Position{1, 7}, PieceType::KNIGHT, PlayerColor::BLACK,
                      board->getWidth(), board->getHeight()),
                  Position{1, 7});
  board->addPiece(PieceFactory::createPiece(
                      Position{6, 7}, PieceType::KNIGHT, PlayerColor::BLACK,
                      board->getWidth(), board->getHeight()),
                  Position{6, 7});

  // Add 2 bishops to white
  board->addPiece(PieceFactory::createPiece(
                      Position{2, 0}, PieceType::BISHOP, PlayerColor::WHITE,
                      board->getWidth(), board->getHeight()),
                  Position{2, 0});
  board->addPiece(PieceFactory::createPiece(
                      Position{5, 0}, PieceType::BISHOP, PlayerColor::WHITE,
                      board->getWidth(), board->getHeight()),
                  Position{5, 0});

  // Add 2 bishops to black
  board->addPiece(PieceFactory::createPiece(
                      Position{2, 7}, PieceType::BISHOP, PlayerColor::BLACK,
                      board->getWidth(), board->getHeight()),
                  Position{2, 7});
  board->addPiece(PieceFactory::createPiece(
                      Position{5, 7}, PieceType::BISHOP, PlayerColor::BLACK,
                      board->getWidth(), board->getHeight()),
                  Position{5, 7});

  // Add 1 queen to white
  board->addPiece(PieceFactory::createPiece(
                      Position{3, 0}, PieceType::QUEEN, PlayerColor::WHITE,
                      board->getWidth(), board->getHeight()),
                  Position{3, 0});

  // Add 1 queen to black
  board->addPiece(PieceFactory::createPiece(
                      Position{3, 7}, PieceType::QUEEN, PlayerColor::BLACK,
                      board->getWidth(), board->getHeight()),
                  Position{3, 7});

  // Add 1 king to white
  board->addPiece(PieceFactory::createPiece(
                      Position{4, 0}, PieceType::KING, PlayerColor::WHITE,
                      board->getWidth(), board->getHeight()),
                  Position{4, 0});

  // Add 1 king to black
  board->addPiece(PieceFactory::createPiece(
                      Position{4, 7}, PieceType::KING, PlayerColor::BLACK,
                      board->getWidth(), board->getHeight()),
                  Position{4, 7});
}

void GameState::standard_checkers_board() {
  // Create a piece of type King for white, place in b1
  board->addPiece(make_unique<Piece>(3, 4, PieceType::KING, PlayerColor::WHITE),
                  Position{3, 4});

  // Create a piece of type King for black, place in a8
  board->addPiece(make_unique<Piece>(4, 3, PieceType::KING, PlayerColor::BLACK),
                  Position{4, 3});

  // Add pieces for white
  for (int i = 0; i < 8; i += 2) {
    board->addPiece(
        make_unique<Checker>(
            make_unique<Piece>(i, 0, PieceType::ROOK, PlayerColor::WHITE), 7),
        Position{i, 0});

    board->addPiece(
        make_unique<Checker>(
            make_unique<Piece>(i + 1, 1, PieceType::ROOK, PlayerColor::WHITE),
            7),
        Position{i + 1, 1});

    board->addPiece(
        make_unique<Checker>(
            make_unique<Piece>(i, 2, PieceType::ROOK, PlayerColor::WHITE), 7),
        Position{i, 2});
  }

  // Add pieces for black
  for (int i = 1; i < 8; i += 2) {
    board->addPiece(
        make_unique<Checker>(
            make_unique<Piece>(i, 7, PieceType::ROOK, PlayerColor::BLACK), 0),
        Position{i, 7});

    board->addPiece(
        make_unique<Checker>(
            make_unique<Piece>(i - 1, 6, PieceType::ROOK, PlayerColor::BLACK),
            0),
        Position{i - 1, 6});

    board->addPiece(
        make_unique<Checker>(
            make_unique<Piece>(i, 5, PieceType::ROOK, PlayerColor::BLACK), 0),
        Position{i, 5});
  }
}
