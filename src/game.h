
#ifndef GAME_H
#define GAME_H

#include "board.h"
#include "player.h"
#include <vector>

class Game {
private:
  Player *white;
  Player *black;
  Player *currentPlayer;

  std::vector<Move> moves;
  int currentMove = 0;
  Board *board;

public:
  Game();
  Board *GetBoard();
  bool IsGameOver() const;
  void AddMove(Move move);
  void Forward();
  void Back();
  bool GetIsBlackTurn();
  bool GetIsWhiteTurn();
  bool MakeMove(Move move);
};

#endif // GAME_H
