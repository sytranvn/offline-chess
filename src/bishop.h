#ifndef BISHOP_H
#define BISHOP_H

#include "piece.h"

class Bishop : public Piece {
public:
  Bishop(bool isWhite, Board *board);
  bool CanMoveTo(Spot *from, Spot *to) const;
};

#endif // BISHOP_H
