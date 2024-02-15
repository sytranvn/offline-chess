#include "piece.h"
#include "board.h"
#include "spot.h"

Piece::Piece(bool isWhite, Board *board) : isWhite(isWhite), board(board){};
char Piece::GetSymbol() { return symbol; }
bool Piece::IsWhite() { return isWhite; }
bool Piece::IsBlack() { return !isWhite; }

bool Piece::CanMoveTo(Spot *from, Spot *to) const {
  int col = to->GetCol();
  int row = to->GetRow();
  Piece *p = to->GetPiece();
  auto a = !(from->GetCol() == col && from->GetRow() == row);
  auto b = (col >= 0 && col < Board::size && row >= 0 && row < Board::size);
  auto c = (p == nullptr || p->IsWhite() != from->GetPiece()->IsWhite());
  return a && b && c;
};
bool Piece::IsDiagonal(Spot *from, Spot *to) const {
  return abs(from->GetCol() - to->GetCol()) ==
         abs(from->GetRow() - to->GetRow());
};
bool Piece::IsVertical(Spot *from, Spot *to) const {
  return from->GetCol() == to->GetCol();
};
bool Piece::IsHorizontal(Spot *from, Spot *to) const {
  return from->GetRow() == to->GetRow();
};
