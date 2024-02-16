#include "board.h"

ChessBoard::PieceCode ChessBoard::pieceCode(PieceType pt) const {
  return (PieceCode)(pt / 2);
};
ChessBoard::PieceType ChessBoard::pieceColor(PieceType pt) const {
  return (PieceType)(pt % 2);
};

Bitboard ChessBoard::getPieceSet(PieceType pt) const {
  return pieceBb[pieceCode(pt)] & pieceBb[pieceColor(pt)];
};
Bitboard ChessBoard::getPawns(ColorType ct) const {
  return pieceBb[nPawn] & pieceBb[ct];
};
Bitboard ChessBoard::getKnights(ColorType ct) const {
  return pieceBb[nKnight] & pieceBb[ct];
};
Bitboard ChessBoard::getBishops(ColorType ct) const {
  return pieceBb[nBishop] & pieceBb[ct];
};
Bitboard ChessBoard::getRooks(ColorType ct) const {
  return pieceBb[nRook] & pieceBb[ct];
};
Bitboard ChessBoard::getQueens(ColorType ct) const {
  return pieceBb[nQeen] & pieceBb[ct];
};
Bitboard ChessBoard::getKings(ColorType ct) const {
  return pieceBb[nKing] & pieceBb[ct];
};
Bitboard ChessBoard::getOccupied(ColorType ct) const { return pieceBb[ct]; };
Bitboard ChessBoard::getOccupied() const {
  return pieceBb[nWhite] | pieceBb[nBlack];
};
Bitboard ChessBoard::getEmpty() const {
  return ~getOccupied(White) & ~getOccupied(Black);
};
size_t ChessBoard::popCount(Bitboard b) const {
  return __builtin_popcountll(b);
};
/**
 * @brief lsb least significant bit
 * @param b bitboard
 * @return index of the least significant bit
 */
size_t ChessBoard::lsb(Bitboard b) const {
  if (b)
    return (size_t)__builtin_ctzll(b);
  return 64;
};
/**
 * @brief msb most significant bit
 * @param b bitboard
 * @return index of the most significant bit
 */
size_t ChessBoard::msb(Bitboard b) const {
  if (b)
    return (size_t)__builtin_clzll(b);
  return 64;
};

std::string ChessBoard::printBitboard(Bitboard b) const {
  std::string buffer(64 + 7, '.');
  int j = 0;
  for (int i = 0; i < 64; i++, j++) {
    if (i && i % 8 == 0)
      buffer[j++] = '\n';
    if (b & (C64(1) << (63 - i)))
      buffer[j] = '1';
  }
  return buffer;
};
