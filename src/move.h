#ifndef MOVE_H
#define MOVE_H

struct Move {
  int fromRow;
  int fromCol;
  int toX;
  int toY;

  Move(int fromX, int fromY, int toX, int toY);
  Move(char move[4]);
};

#endif // MOVE_H
