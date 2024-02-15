#ifndef PIECE_H
#define PIECE_H

#include <iostream>

// Forward declaration
class Spot;
class Board;


class Piece {
protected:
  char symbol;
  bool isWhite;
  Board *board;

  bool IsDiagonal(Spot *from, Spot *to) const;
  bool IsVertical(Spot *from, Spot *to) const;
  bool IsHorizontal(Spot *from, Spot *to) const;

public:
  Piece(bool isWhite, Board *board);
  virtual char GetSymbol();
  bool IsWhite();
  bool IsBlack();
  virtual bool CanMoveTo(Spot *from, Spot *to) const;

  virtual ~Piece() = default;
};

#endif // PIECE_H
