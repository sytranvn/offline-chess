#ifndef ENGINE_H
#define ENGINE_H

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

// constants
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

#endif // ENGINE_H
