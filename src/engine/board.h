#ifndef BOARD_H
#define BOARD_H

#include <cstdint>
// https://www.chessprogramming.org/Bitboards

typedef uint64_t Bitboard;

class ChessBoard {
  Bitboard pieceBb[8];

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

  PieceCode pieceCode(PieceType pt) const { return (PieceCode)(pt / 2); };
  PieceType pieceColor(PieceType pt) const { return (PieceType)(pt % 2); };

  Bitboard getPieceSet(PieceType pt) const {
    return pieceBb[pieceCode(pt)] & pieceBb[pieceColor(pt)];
  };
  Bitboard getPawns(ColorType ct) const {
    return pieceBb[nPawn] & pieceBb[ct];
  };
  Bitboard getKnights(ColorType ct) const {
    return pieceBb[nKnight] & pieceBb[ct];
  };
  Bitboard getBishops(ColorType ct) const {
    return pieceBb[nBishop] & pieceBb[ct];
  };
  Bitboard getRooks(ColorType ct) const {
    return pieceBb[nRook] & pieceBb[ct];
  };
  Bitboard getQueens(ColorType ct) const {
    return pieceBb[nQeen] & pieceBb[ct];
  };
  Bitboard getKings(ColorType ct) const {
    return pieceBb[nKing] & pieceBb[ct];
  };
  Bitboard getOccupied(ColorType ct) const { return pieceBb[ct]; };
  Bitboard getOccupied() const { return pieceBb[nWhite] | pieceBb[nBlack]; };
  Bitboard getEmpty() const {
    return ~getOccupied(White) & ~getOccupied(Black);
  };
};

#endif // BOARD_H
