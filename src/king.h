#ifndef KING_H
#define KING_H

#include "move.h"
#include "piece.h"
#include "spot.h"

#include <cmath>
#include <vector>

class King : public Piece {
private:
  bool moved = false;

public:
  King(bool isWhite, Board *board);
  bool CanMoveTo(Spot *from, Spot *to) const;
  std::vector<Move> LegalMoves(Spot *from, Board *board);
  bool Moved() { return moved; }
  bool Checked(Board *board);
};

#endif // KING_H
