#include "pawn.h"
#include "board.h"
#include "spot.h"

Pawn::Pawn(bool isWhite, Board *board) : Piece(isWhite, board) {
  symbol = isWhite ? 'P' : 'p';
};
bool Pawn::CanMoveTo(Spot *from, Spot *to) const {
  if (Piece::CanMoveTo(from, to)) {
    auto p = from->GetPiece();
    int nextRow = to->GetRow() - from->GetRow();
    int nextCol = to->GetCol() - from->GetCol();
    if (p->IsWhite() && nextRow <= 0 || p->IsBlack() && nextRow >= 0) {
      return false;
    } else if (nextCol == 0) {
      // Only move forward
      // Check if the pawn is moving 2 steps
      if (abs(nextRow) > 2) {
        return false;
      } else if (abs(nextRow) == 2) {
        if (p->IsWhite() && from->GetRow() != 1 ||
            p->IsBlack() && from->GetRow() != 6) {
          return false;
        }
      }
      int direction = p->IsWhite() ? 1 : -1;
      for (int i = 1; i < abs(nextRow); ++i) {
        if (from->GetBoard()->GetPiece(from->GetRow() + i * direction,
                                       from->GetCol()) != nullptr) {
          return false;
        }
      }
      // Check if the spot is empty
      return to->GetPiece() == nullptr;
    } else if (abs(nextCol) == 1) {
      // Check if the spot can capture, we don't need to check piece color
      // because we did in Piece::CanMoveTo
      return abs(nextRow) == 1 && to->GetPiece() != nullptr;
    } else
      return false;
  }
  return false;
}
