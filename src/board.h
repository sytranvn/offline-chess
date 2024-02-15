#ifndef BOARD_H
#define BOARD_H

#include "bishop.h"
#include "king.h"
#include "knight.h"
#include "move.h"
#include "pawn.h"
#include "piece.h"
#include "piece_factory.h"
#include "queen.h"
#include "rook.h"
#include "spot.h"
#include <iostream>
#include <string>

class Board {
public:
  static const int size = 8;

private:
  Spot *spots[size][size];
  Spot *whiteKingSpot;
  Spot *blackKingSpot;

public:
  Board();
  /**
   * @brief Get the Piece object at position
   */
  Piece *GetPiece(int row, int col);
  Spot *GetSpot(int row, int col);
  void MovePiece(int fromRow, int fromCol, int toRow, int toCol);
  void MovePiece(Move move);
  std::string ToString();
  Spot *GetWhiteKingSpot() { return whiteKingSpot; }
  Spot *GetBlackKingSpot() { return blackKingSpot; }
};

#endif // BOARD_H
