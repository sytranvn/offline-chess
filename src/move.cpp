#include "move.h"

Move::Move(int fromX, int fromY, int toX, int toY)
    : fromRow(fromX), fromCol(fromY), toX(toX), toY(toY){};

Move::Move(char move[4]) {
  int y = move[0] - 'a';
  int x = move[1] - '0';
  int toY = move[2] - 'a';
  int toX = move[3] - '0';
  Move(x, y, toX, toY);
};
