#ifndef BOARD_H
#define BOARD_H

#include <array>
#include <cstddef>
#include <stdio.h>
#include <string>
// https://www.chessprogramming.org/Bitboards

typedef unsigned long long Bitboard;
/** Constant Bitboard */
#define CBB(constantU64) constantU64##ULL

// clang-format off
enum EnumSquare {
  a1, b1, c1, d1, e1, f1, g1, h1,
  a2, b2, c2, d2, e2, f2, g2, h2,
  a3, b3, c3, d3, e3, f3, g3, h3,
  a4, b4, c4, d4, e4, f4, g4, h4,
  a5, b5, c5, d5, e5, f5, g5, h5,
  a6, b6, c6, d6, e6, f6, g6, h6,
  a7, b7, c7, d7, e7, f7, g7, h7,
  a8, b8, c8, d8, e8, f8, g8, h8
};
// clang-format on

class ChessBoard {
  Bitboard pieceBb[8] = {0};
  Bitboard nortFill(Bitboard gen);
  Bitboard soutFill(Bitboard gen);
  void init(Bitboard in[8]);

public:
  ChessBoard();
  ChessBoard(Bitboard in[8]);
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
    // clang-format off
    Empty  = 0,
    Pawn   = nPawn,
    Knight = nKnight,
    Bishop = nBishop,
    Rook   = nRook,
    Queen  = nQeen,
    King   = nKing
    // clang-format on
  };
  enum PieceCode {
    // clang-format off
    WhitePawn   = nPawn   * 2 + nWhite,
    WhiteKnight = nKnight * 2 + nWhite,
    WhiteBishop = nBishop * 2 + nWhite,
    WhiteRook   = nRook   * 2 + nWhite,
    WhiteQueen  = nQeen   * 2 + nWhite,
    WhiteKing   = nKing   * 2 + nWhite,

    BlackPawn   = nPawn   * 2 + nBlack,
    BlackKnight = nKnight * 2 + nBlack,
    BlackBishop = nBishop * 2 + nBlack,
    BlackRook   = nRook   * 2 + nBlack,
    BlackQueen   = nQeen   * 2 + nBlack,
    BlackKing   = nKing   * 2 + nBlack,
    // clang-format on
  };

  enum Neighbour {
    // clang-format off
    N  = 8,
    S  = -8,
    E  = 1,
    W  = -1,
    NE = N + E,
    NW = N + W,
    SE = S + E,
    SW = S + W
    // clang-format on
  };

  PieceType pieceType(PieceCode pt);
  ColorType pieceColor(PieceCode pt);

  Bitboard getPieceSet(PieceCode pt);
  Bitboard getPawns(ColorType ct);
  Bitboard getKnights(ColorType ct);
  Bitboard getBishops(ColorType ct);
  Bitboard getRooks(ColorType ct);
  Bitboard getQueens(ColorType ct);
  Bitboard getKings(ColorType ct);
  Bitboard getOccupied(ColorType ct);
  Bitboard getOccupied();
  Bitboard getEmpty();
  size_t popCount(Bitboard b);
  /**
   * @brief lsb least significant bit
   * @param b bitboard
   * @return index of the least significant bit
   */
  size_t lsb(Bitboard b);
  /**
   * @brief msb most significant bit
   * @param b bitboard
   * @return index of the most significant bit
   */
  size_t msb(Bitboard b);
  std::string printBitboard(Bitboard b);
  void fillChar(Bitboard b, char ch, std::string &out);
  std::string toString();
  std::string fillChar();
  Bitboard wFrontFill(Bitboard wpawns);
  Bitboard wRearFill(Bitboard wpawns);
  Bitboard bFrontFill(Bitboard bpawns);
  Bitboard bRearFill(Bitboard bpawns);
  Bitboard fileFill(Bitboard gen);
  /**
   * @brief to rank 8 direction
   */
  Bitboard soutOne(Bitboard b);
  /**
   * @brief to rank 1 direction
   */
  Bitboard nortOne(Bitboard b);
  /**
   * @brief to H file
   */
  Bitboard eastOne(Bitboard b);
  Bitboard noEaOne(Bitboard b);
  Bitboard soEaOne(Bitboard b);
  /**
   * @brief to A file
   */
  Bitboard westOne(Bitboard b);
  Bitboard soWeOne(Bitboard b);
  Bitboard noWeOne(Bitboard b);
  Bitboard genShift(Bitboard b, int bits);
  /**
   * =====================================
   * Pawn moves
   * =====================================
   */
  Bitboard wSinglePushTargets(Bitboard wpawns, Bitboard empty);
  Bitboard wSinglePushTargets();
  Bitboard wDblPushTargets(Bitboard wpawns, Bitboard empty);

  Bitboard bSinglePushTargets(Bitboard bpawns, Bitboard empty);
  Bitboard bSinglePushTargets();
  Bitboard bDblPushTargets(Bitboard bpawns, Bitboard empty);

  Bitboard putPiece(Bitboard b, EnumSquare s);
  Bitboard delPiece(Bitboard b, EnumSquare s);
};

const Bitboard aFile = CBB(0x0101010101010101);
const Bitboard bFile = aFile << 1;
const Bitboard cFile = aFile << 2;
const Bitboard dFile = aFile << 3;
const Bitboard eFile = aFile << 4;
const Bitboard fFile = aFile << 5;
const Bitboard gFile = aFile << 6;
const Bitboard hFile = CBB(0x8080808080808080);
const Bitboard notAFile = ~aFile; // ~0x0101010101010101
const Bitboard notHFile = ~hFile; // ~0x8080808080808080
const Bitboard rank1 = CBB(0x00000000000000FF);
const Bitboard rank2 = rank1 << (1 * 8);
const Bitboard rank3 = rank1 << (2 * 8);
const Bitboard rank4 = rank1 << (3 * 8);
const Bitboard rank5 = rank1 << (4 * 8);
const Bitboard rank6 = rank1 << (5 * 8);
const Bitboard rank7 = rank1 << (6 * 8);
const Bitboard rank8 = rank1 << (7 * 8);
const Bitboard a1H8Diag = CBB(0x8040201008040201);
const Bitboard h1A8Diag = CBB(0x0102040810204080);
const Bitboard darkSqs = CBB(0xAA55AA55AA55AA55);
const Bitboard lighSqs = CBB(0x55AA55AA55AA55AA);

#endif // BOARD_H
