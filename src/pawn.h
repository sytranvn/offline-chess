#ifndef PAWN_H
#define PAWN_H

#include "piece.h"
#include <cmath>

class Pawn : public Piece {
private:
public:
  Pawn(bool isWhite, Board *board);
  bool CanMoveTo(Spot *from, Spot *to) const;
};

#endif // PAWN_H
