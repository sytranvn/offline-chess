#include "board.h"
#include "game.h"
#include <algorithm>
#include <stdexcept>
#include <string>
#include <vector>

Board::Board() {
  for (int i = 0; i < 8; ++i) {
    spots[1][i] = new Spot(1, i, new Pawn(true, this), (1 + i) % 2, this);
    spots[6][i] = new Spot(6, i, new Pawn(false, this), (6 + i) % 2, this);
  }
  const char *pieces = "RNBQKBNR";
  for (int i = 0; i < 8; ++i) {
    spots[0][i] =
        new Spot(0, i, PieceFactory::CreatePiece(pieces[i], 0, i, true, this),
                 (0 + i) % 2, this);
    spots[7][i] =
        new Spot(7, i, PieceFactory::CreatePiece(pieces[i], 7, i, false, this),
                 (7 + i) % 2, this);
  }
  for (int i = 2; i < 6; ++i) {
    for (int j = 0; j < 8; ++j) {
      spots[i][j] = new Spot(i, j, nullptr, (i + j) % 2, this);
    }
  }
};

std::string Board::ToString() {
  std::string finalResult = "================\n";
  for (int i = 7; i >= 0; --i) {
    finalResult += std::to_string(i + 1);

    for (int j = 0; j < 8; ++j) {
      auto p = spots[i][j]->GetPiece();
      if (p != nullptr) {
        finalResult += p->GetSymbol();
      } else {
        finalResult += spots[i][j]->IsWhite() ? '.' : '#';
      }
    }
    finalResult += "\n";
  }
  finalResult += " abcdefgh\n================\n";
  return finalResult;
};

Piece *Board::GetPiece(int row, int col) {
  return spots[row][col]->GetPiece();
};

Spot *Board::GetSpot(int row, int col) { return spots[row][col]; };

void Board::MovePiece(int fromRow, int fromCol, int toRow, int toCol) {
  auto from = spots[fromRow][fromCol];
  auto to = spots[toRow][toCol];
  if (from->GetPiece() == nullptr) {
    throw std::runtime_error("No piece at source");
  }
  auto p = from->GetPiece();
  if (p->CanMoveTo(from, to)) {
    to->SetPiece(p);
    from->SetPiece(nullptr);
  } else {
    throw std::runtime_error("Invalid move");
  }
};

void Board::MovePiece(struct Move move) {
  MovePiece(move.fromRow, move.fromCol, move.toX, move.toY);
}
