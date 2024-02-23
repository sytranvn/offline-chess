#ifndef BOARD_H
#define BOARD_H

#include "engine.h"
#include "move.h"
#include <cstddef>
#include <stdio.h>
#include <string>
// https://www.chessprogramming.org/Bitboards

class ChessBoard {
  Bitboard pieceBb[8] = {0};
  Bitboard nortFill(Bitboard gen);
  Bitboard soutFill(Bitboard gen);
  void init(Bitboard in[8]);

public:
  ChessBoard();
  ChessBoard(Bitboard in[8]);
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

  // =====================================
  // Bitboard operations
  // =====================================
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

  // =====================================
  // Pawns fills
  // =====================================
  Bitboard wFrontFill(Bitboard wpawns);
  Bitboard wRearFill(Bitboard wpawns);
  Bitboard bFrontFill(Bitboard bpawns);
  Bitboard bRearFill(Bitboard bpawns);
  Bitboard fileFill(Bitboard gen);

  /**
   * =====================================
   * Pawn moves
   * =====================================
   */
  Bitboard wSinglePushTargets(Bitboard wpawns, Bitboard empty);
  Bitboard wSinglePushTargets();
  Bitboard wDblPushTargets(Bitboard wpawns, Bitboard empty);

  Bitboard wPawnsAble2Push(Bitboard b, Bitboard empty);
  Bitboard wPawnsAble2Push();

  Bitboard wPawnsAble2DblPush(Bitboard b, Bitboard empty);
  Bitboard wPawnsAble2DblPush();

  Bitboard bSinglePushTargets(Bitboard bpawns, Bitboard empty);
  Bitboard bSinglePushTargets();
  Bitboard bDblPushTargets(Bitboard bpawns, Bitboard empty);

  Bitboard bPawnsAble2Push(Bitboard b, Bitboard empty);
  Bitboard bPawnsAble2Push();

  Bitboard bPawnsAble2DblPush(Bitboard b, Bitboard empty);
  Bitboard bPawnsAble2DblPush();

  Bitboard putPiece(Bitboard b, EnumSquare s);
  Bitboard delPiece(Bitboard b, EnumSquare s);

  void quiteMove(Move *move);
};

#endif // BOARD_H
