#ifndef BOARD_H
#define BOARD_H

#include <cstddef>
#include <stdio.h>
#include <string>
// https://www.chessprogramming.org/Bitboards

typedef unsigned long long Bitboard;
#define C64(constantU64) constantU64##ULL

class ChessBoard {
  Bitboard pieceBb[8] = {0};

public:
  enum enumPiece {
    nWhite,
    nBlack,
    nPawn,
    nKnight,
    nBishop,
    nRook,
    nQeen,
    nKing,
  };
  enum ColorType { White = nWhite, Black = nBlack };
  enum PieceType {
    Empty = 0,
    Pawn = nPawn,
    Knight = nKnight,
    Bishop = nBishop,
    Rook = nRook,
    Queen = nQeen,
    King = nKing
  };
  enum PieceCode {
    wPawn = nPawn * 2 + nWhite,
    wKnight = nKnight * 2 + nWhite,
    wBishop = nBishop * 2 + nWhite,
    wRook = nRook * 2 + nWhite,
    wQueen = nQeen * 2 + nWhite,
    wKing = nKing * 2 + nWhite,

    bPawn = nPawn * 2 + nBlack,
    bKnight = nKnight * 2 + nBlack,
    bBishop = nBishop * 2 + nBlack,
    bRook = nRook * 2 + nBlack,
    bQuen = nQeen * 2 + nBlack,
    bKing = nKing * 2 + nBlack,
  };

  enum Neighbour {
    N = 8,
    S = -8,
    E = 1,
    W = -1,
    NE = N + E,
    NW = N + W,
    SE = S + E,
    SW = S + W
  };

  PieceCode pieceCode(PieceType pt) const;
  PieceType pieceColor(PieceType pt) const;

  Bitboard getPieceSet(PieceType pt) const;
  Bitboard getPawns(ColorType ct) const;
  Bitboard getKnights(ColorType ct) const;
  Bitboard getBishops(ColorType ct) const;
  Bitboard getRooks(ColorType ct) const;
  Bitboard getQueens(ColorType ct) const;
  Bitboard getKings(ColorType ct) const;
  Bitboard getOccupied(ColorType ct) const;
  Bitboard getOccupied() const;
  Bitboard getEmpty() const;
  size_t popCount(Bitboard b) const;
  /**
   * @brief lsb least significant bit
   * @param b bitboard
   * @return index of the least significant bit
   */
  size_t lsb(Bitboard b) const;
  /**
   * @brief msb most significant bit
   * @param b bitboard
   * @return index of the most significant bit
   */
  size_t msb(Bitboard b) const;
  std::string printBitboard(Bitboard b) const;
};

#endif // BOARD_H
