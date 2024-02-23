#include "board.h"
#include <iostream>
#include <string>

void ChessBoard::init(Bitboard in[8]) {
  for (int i = 0; i < 8; i++) {
    pieceBb[i] = in[i];
  }
}
ChessBoard::ChessBoard(Bitboard in[8]) { init(in); };

ChessBoard::ChessBoard() {

  Bitboard p1 = CBB(1);
  Bitboard in[8] = {
      // white
      rank1 | rank2,
      // black
      rank8 | rank7,
      // pawn
      rank2 | rank7,
      // knight
      (rank1 | rank8) & (bFile | gFile),
      // bishop
      (rank1 | rank8) & (cFile | fFile),
      // rook
      (rank1 | rank8) & (aFile | hFile),
      // queen
      (rank1 | rank8) & dFile,
      // king
      (rank1 | rank8) & eFile,
  };
  init(in);
};

ChessBoard::PieceType ChessBoard::pieceType(ChessBoard ::PieceCode pt) {
  return (PieceType)(pt / 2);
};
ChessBoard::ColorType ChessBoard::pieceColor(ChessBoard::PieceCode pt) {
  return (ColorType)(pt % 2);
};

Bitboard ChessBoard::getPieceSet(ChessBoard::PieceCode pt) {
  return pieceBb[pieceType(pt)] & pieceBb[pieceColor(pt)];
};
Bitboard ChessBoard::getPawns(ColorType ct) {
  return pieceBb[nPawn] & pieceBb[ct];
};
Bitboard ChessBoard::getKnights(ColorType ct) {
  return pieceBb[nKnight] & pieceBb[ct];
};
Bitboard ChessBoard::getBishops(ColorType ct) {
  return pieceBb[nBishop] & pieceBb[ct];
};
Bitboard ChessBoard::getRooks(ColorType ct) {
  return pieceBb[nRook] & pieceBb[ct];
};
Bitboard ChessBoard::getQueens(ColorType ct) {
  return pieceBb[nQeen] & pieceBb[ct];
};
Bitboard ChessBoard::getKings(ColorType ct) {
  return pieceBb[nKing] & pieceBb[ct];
};
Bitboard ChessBoard::getOccupied(ColorType ct) { return pieceBb[ct]; };
Bitboard ChessBoard::getOccupied() {
  return pieceBb[nWhite] | pieceBb[nBlack];
};
Bitboard ChessBoard::getEmpty() {
  return ~getOccupied(White) & ~getOccupied(Black);
};
size_t ChessBoard::popCount(Bitboard b) { return __builtin_popcountll(b); };
/**
 * @brief lsb least significant bit
 * @param b bitboard
 * @return index of the least significant bit
 */
size_t ChessBoard::lsb(Bitboard b) {
  if (b)
    return (size_t)__builtin_ctzll(b);
  return 64;
};
/**
 * @brief msb most significant bit
 * @param b bitboard
 * @return index of the most significant bit
 */
size_t ChessBoard::msb(Bitboard b) {
  if (b)
    return (size_t)__builtin_clzll(b);
  return 64;
};

std::string ChessBoard::printBitboard(Bitboard b) {
  std::string buffer(64 + 7, '.');
  int j = 0;
  for (int i = 0; i < 64; i++, j++) {
    if (i && i % 8 == 0)
      buffer[j++] = '\n';
    if (b & (CBB(1) << (63 - i))) // reverse order so white side is at bottom
      buffer[j] = '1';
  }
  return buffer;
};

void ChessBoard::fillChar(Bitboard b, char ch, std::string &out) {
  for (int i = 0; i < 64; i++) {
    if (b & (CBB(1) << (63 - i))) // reverse order so white side is at bottom
      out[i / 8 * 9 + i % 8] = ch;
  }
}

std::string ChessBoard::toString() {
  Bitboard b = CBB(0);
  for (int i = 0; i < 8; i++) {
    b |= pieceBb[i];
  }
  return printBitboard(b);
}

std::string ChessBoard::fillChar() {
  std::string out(64 + 8, ' ');
  fillChar(darkSqs, '0', out);
  fillChar(pieceBb[nPawn] & pieceBb[nWhite], 'P', out);
  fillChar(pieceBb[nRook] & pieceBb[nWhite], 'R', out);
  fillChar(pieceBb[nKnight] & pieceBb[nWhite], 'N', out);
  fillChar(pieceBb[nBishop] & pieceBb[nWhite], 'B', out);
  fillChar(pieceBb[nQeen] & pieceBb[nWhite], 'Q', out);
  fillChar(pieceBb[nKing] & pieceBb[nWhite], 'K', out);

  fillChar(pieceBb[nPawn] & pieceBb[nBlack], 'p', out);
  fillChar(pieceBb[nRook] & pieceBb[nBlack], 'r', out);
  fillChar(pieceBb[nKnight] & pieceBb[nBlack], 'n', out);
  fillChar(pieceBb[nBishop] & pieceBb[nBlack], 'b', out);
  fillChar(pieceBb[nQeen] & pieceBb[nBlack], 'q', out);
  fillChar(pieceBb[nKing] & pieceBb[nBlack], 'k', out);
  for (int i = 8; i < 64 + 8; i += 9)
    out[i] = '\n';
  return out;
}

Bitboard ChessBoard::nortFill(Bitboard gen) {
  // the filled lines will be doubled every time so 3 shifts will fill all 8
  // ranks
  gen |= (gen << 8);
  gen |= (gen << 16);
  gen |= (gen << 32);
  return gen;
};
Bitboard ChessBoard::soutFill(Bitboard gen) {
  // the filled lines will be doubled every time so 3 shifts will fill all 8
  // ranks
  gen |= (gen >> 8);
  gen |= (gen >> 16);
  gen |= (gen >> 32);
  return gen;
};
Bitboard ChessBoard::wFrontFill(Bitboard wpawns) { return nortFill(wpawns); };
Bitboard ChessBoard::wRearFill(Bitboard wpawns) { return soutFill(wpawns); };
Bitboard ChessBoard::bFrontFill(Bitboard bpawns) { return nortFill(bpawns); };
Bitboard ChessBoard::bRearFill(Bitboard bpawns) { return soutFill(bpawns); };
Bitboard ChessBoard ::fileFill(Bitboard gen) {
  return nortFill(gen) | soutFill(gen);
};
Bitboard ChessBoard::soutOne(Bitboard b) { return b >> 8; };
Bitboard ChessBoard::nortOne(Bitboard b) { return b << 8; };
Bitboard ChessBoard::eastOne(Bitboard b) { return (b << 1) & notAFile; }
Bitboard ChessBoard::noEaOne(Bitboard b) { return (b << 9) & notAFile; }
Bitboard ChessBoard::soEaOne(Bitboard b) { return (b >> 7) & notAFile; }
Bitboard ChessBoard::westOne(Bitboard b) { return (b >> 1) & notHFile; }
Bitboard ChessBoard::soWeOne(Bitboard b) { return (b >> 9) & notHFile; }
Bitboard ChessBoard::noWeOne(Bitboard b) { return (b << 7) & notHFile; }
Bitboard ChessBoard::genShift(Bitboard b, int bits) {
  return bits > 0 ? (b << bits) : (b >> -bits);
};
Bitboard ChessBoard::wSinglePushTargets(Bitboard wpawns, Bitboard empty) {
  return nortOne(wpawns) & empty;
};
Bitboard ChessBoard::wSinglePushTargets() {
  return wSinglePushTargets(getPawns(White), getEmpty());
};
Bitboard ChessBoard::wDblPushTargets(Bitboard wpawns, Bitboard empty) {
  Bitboard singlePush = wSinglePushTargets(wpawns, empty);
  return nortOne(singlePush) & empty & rank4;
};

Bitboard ChessBoard::wPawnsAble2Push(Bitboard b, Bitboard empty) {
  // empty squares go opposite direction of white pawns
  return nortOne(empty) & b;
};
Bitboard ChessBoard::wPawnsAble2Push() {
  return wPawnsAble2Push(getPawns(White), getEmpty());
};

Bitboard ChessBoard::wPawnsAble2DblPush(Bitboard b, Bitboard empty) {
  Bitboard emptyRank3 = nortOne(empty & rank4) & empty;
  return wPawnsAble2Push(b, emptyRank3);
};
Bitboard ChessBoard::wPawnsAble2DblPush() {
  return wPawnsAble2DblPush(getPawns(White), getEmpty());
};

Bitboard ChessBoard::bSinglePushTargets(Bitboard bpawns, Bitboard empty) {
  return nortOne(bpawns) & empty;
};
Bitboard ChessBoard::bSinglePushTargets() {
  return bSinglePushTargets(getPawns(Black), getEmpty());
};
Bitboard ChessBoard::bDblPushTargets(Bitboard bpawns, Bitboard empty) {
  Bitboard singlePush = bSinglePushTargets(bpawns, empty);
  return nortOne(singlePush) & empty & rank4;
};

Bitboard ChessBoard::bPawnsAble2Push(Bitboard b, Bitboard empty) {
  // empty squares go opposite direction of black pawns
  return soutOne(empty) & b;
};
Bitboard ChessBoard::bPawnsAble2Push() {
  return bPawnsAble2Push(getPawns(Black), getEmpty());
};

Bitboard ChessBoard::bPawnsAble2DblPush(Bitboard b, Bitboard empty) {
  Bitboard emptyRank6 = soutOne(empty & rank5) & empty;
  return bPawnsAble2Push(b, emptyRank6);
};
Bitboard ChessBoard::bPawnsAble2DblPush() {
  return bPawnsAble2DblPush(getPawns(Black), getEmpty());
};

Bitboard ChessBoard::putPiece(Bitboard b, EnumSquare s) {
  return b | (CBB(1) << s);
};
Bitboard ChessBoard::delPiece(Bitboard b, EnumSquare s) {
  return b ^ (CBB(1) << s);
};
