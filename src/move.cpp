#include "move.h"

Move::Move(int fromRow, int fromCol, int toRow, int toCol)
    : fromRow(fromRow), fromCol(fromCol), toRow(toRow), toCol(toCol){};

Move::Move(char move[4]) {
  int y = move[0] - 'a';
  int x = move[1] - '0';
  int toY = move[2] - 'a';
  int toX = move[3] - '0';
  Move(x, y, toX, toY);
};
