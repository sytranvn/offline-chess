#include "rook.h"
#include "board.h"
#include "spot.h"

Rook::Rook(bool isWhite, Board *board) : Piece(isWhite, board) {
  symbol = isWhite ? 'R' : 'r';
};

bool Rook::CanMoveTo(Spot *from, Spot *to) const {
  if (Piece::CanMoveTo(from, to)) {
    Piece *p = to->GetPiece();
    if (IsVertical(from, to) || IsHorizontal(from, to)) {
      int nextCol = to->GetCol() - from->GetCol();
      int nextRow = to->GetRow() - from->GetRow();
      int direction = nextRow > 0 ? 1 : -1;
      for (int i = 1; i < abs(nextRow); ++i) {
        if (from->GetBoard()->GetPiece(from->GetRow() + i * direction,
                                       from->GetCol()) != nullptr) {
          return false;
        }
      }
      direction = nextCol > 0 ? 1 : -1;
      for (int i = 1; i < abs(nextCol); ++i) {
        if (from->GetBoard()->GetPiece(
                from->GetRow(), from->GetCol() + i * direction) != nullptr) {
          return false;
        }
      }
      return true;
    }
    return false;
  }
  return false;
}
