#include "king.h"
#include "board.h"
#include <vector>

King::King(bool isWhite, Board *board) : Piece(isWhite, board) {
  symbol = isWhite ? 'K' : 'k';
};

bool King::CanMoveTo(Spot *from, Spot *to) const {
  if (Piece::CanMoveTo(from, to)) {
    return (std::abs(from->GetCol() - to->GetCol()) <= 1) &&
           (std::abs(from->GetRow() - to->GetRow()) <= 1);
  }
  std::cout << "King can't move there" << std::endl;
  return false;
};

std::vector<Move> King::LegalMoves(Spot *from, Board *board) {
  std::vector<Move> result;
  for (int i : {-1, 0, 1}) {
    for (int j : {-1, 0, 1}) {
      if (i == 0 && j == 0) {
        continue;
      }
      int toX = from->GetCol() + i;
      int toY = from->GetRow() + j;
      Spot *to = board->GetSpot(toX, toY);
      if (CanMoveTo(from, to)) {
        Move m =
            Move{from->GetCol(), from->GetRow(), to->GetCol(), to->GetRow()};
        result.push_back(m);
      }
    }
  }
  return result;
}

bool King::Checked(Board *board) {
  int row = 0;
  int col = 0;
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      Spot *s = board->GetSpot(i, j);
      if (s->GetPiece() != nullptr) {
        if (s->GetPiece()->IsWhite() != IsWhite()) {
          if (s->GetPiece()->CanMoveTo(s, board->GetSpot(col, row))) {
            return true;
          }
        }
      }
    }
  }
  return false;
}
