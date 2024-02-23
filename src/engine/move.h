#ifndef MOVE_H
#define MOVE_H
// https://www.chessprogramming.org/Encoding_Moves

#include "engine/engine.h"

struct Move {
  EnumSquare from;
  EnumSquare to;
  PieceType piece;
  ColorType color;
  PieceType capturePiece;
  ColorType captureColor;
  PieceType promotion;
};

#endif // MOVE_H
