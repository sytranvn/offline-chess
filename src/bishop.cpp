#include "bishop.h"
#include "board.h"
#include "piece.h"
#include "spot.h"

Bishop::Bishop(bool isWhite, Board *board) : Piece(isWhite, board) {
  symbol = isWhite ? 'B' : 'b';
}

bool Bishop::CanMoveTo(Spot *from, Spot *to) const {
  if (Piece::CanMoveTo(from, to)) {
    if (IsDiagonal(from, to)) {
      int rowD = from->GetRow() < to->GetRow() ? 1 : -1;
      int colD = from->GetCol() < to->GetCol() ? 1 : -1;
      for (int i = 1; i < abs(from->GetCol() - to->GetCol()); i++) {
        if (board->GetPiece(from->GetRow() + i * rowD,
                            from->GetCol() + i * colD) != nullptr) {
          return false;
        }
      }
      return true;
    }
    return false;
  }
  return false;
}
