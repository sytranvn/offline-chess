#ifndef KNIGHT_H
#define KNIGHT_H

#include "piece.h"

class Knight : public Piece {
public:
  Knight(bool isWhite, Board *board);
  bool CanMoveTo(Spot *from, Spot *to) const;
};

#endif // KNIGHT_H
