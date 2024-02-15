#ifndef PIECE_FACTORY_H
#define PIECE_FACTORY_H

#include "bishop.h"
#include "king.h"
#include "knight.h"
#include "pawn.h"
#include "piece.h"
#include "queen.h"
#include "rook.h"

class PieceFactory {
public:
  static Piece *CreatePiece(char type, int x, int y, bool isWhite,
                            Board *board) {
    switch (type) {
    case 'K':
      return new King(isWhite, board);
    case 'Q':
      return new Queen(isWhite, board);
    case 'R':
      return new Rook(isWhite, board);
    case 'B':
      return new Bishop(isWhite, board);
    case 'N':
      return new Knight(isWhite, board);
    case 'P':
      return new Pawn(isWhite, board);
    default:
      return nullptr;
    }
  }
};

#endif // PIECE_FACTORY_H
