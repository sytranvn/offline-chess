#include "queen.h"
#include "board.h"
#include "spot.h"

Queen::Queen(bool isWhite, Board *board) : Piece(isWhite, board) {
  symbol = isWhite ? 'Q' : 'q';
};

bool Queen::CanMoveTo(Spot *from, Spot *to) const {
  if (Piece::CanMoveTo(from, to)) {
    int rowD = from->GetRow() < to->GetRow() ? 1 : -1;
    int colD = from->GetCol() < to->GetCol() ? 1 : -1;
    if (IsDiagonal(from, to)) {
      for (int i = 1; i < abs(from->GetCol() - to->GetCol()); i++) {
        if (board->GetPiece(from->GetRow() + i * rowD,
                            from->GetCol() + i * colD) != nullptr) {
          return false;
        }
      }
    } else if (IsVertical(from, to)) {
      for (int i = 1; i < abs(from->GetCol() - to->GetCol()); ++i) {
        if (from->GetBoard()->GetPiece(from->GetRow() + i * rowD,
                                       from->GetCol()) != nullptr) {
          return false;
        }
      }
    } else if (IsHorizontal(from, to)) {
      for (int i = 1; i < abs(from->GetRow() - to->GetRow()); ++i) {
        if (from->GetBoard()->GetPiece(from->GetRow(),
                                       from->GetCol() + i * colD) != nullptr) {
          return false;
        }
      }
    } else
      return false;

    return true;
  }
  return false;
}
