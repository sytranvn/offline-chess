#include "knight.h"
#include "spot.h"

Knight::Knight(bool isWhite, Board *board) : Piece(isWhite, board) {
  symbol = isWhite ? 'N' : 'n';
};
bool Knight::CanMoveTo(Spot *from, Spot *to) const {
  if (Piece::CanMoveTo(from, to)) {
    return abs((from->GetCol() - to->GetCol()) *
               (from->GetRow() - to->GetRow())) == 2;
  }
  return false;
};
