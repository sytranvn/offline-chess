#ifndef SPOT_H
#define SPOT_H

#include "piece.h"

class Spot {
private:
  int col;
  int row;
  bool isWhite;
  Piece *piece;
  Board *board;

public:
  Spot(int row, int col, Piece *piece, bool isWhite, Board *board);
  Piece *GetPiece();
  void SetPiece(Piece *p);
  bool IsWhite() { return isWhite; };
  int GetCol();
  int GetRow();
  Board *GetBoard() { return board; }
};

#endif // SPOT_H
