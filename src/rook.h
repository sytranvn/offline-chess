#ifndef ROOK_H
#define ROOK_H

#include "piece.h"

class Rook : public Piece {
public:
  Rook(bool isWhite, Board *board);
  bool CanMoveTo(Spot *from, Spot *to) const;
};

#endif // ROOK_H
