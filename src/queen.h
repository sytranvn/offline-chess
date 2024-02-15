#ifndef QUEEN_H
#define QUEEN_H

#include "piece.h"

class Queen : public Piece {
public:
  Queen(bool isWhite, Board *board);
  bool CanMoveTo(Spot *from, Spot *to) const;
};

#endif // QUEEN_H
