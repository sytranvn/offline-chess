#include "engine/board.h"
#include "engine/engine.h"
#include <gtest/gtest.h>

class ChessBoardTest : public ::testing::Test {
protected:
  ChessBoard board;
  void setUp() { board = ChessBoard(); }
};

#define EXPECT_EQ_BOARD(a, b)                                                  \
  EXPECT_EQ(a, b) << board.printBitboard(a) << "\n!=\n"                        \
                  << board.printBitboard(b)

// =====================================
// Board initialization
// =====================================
TEST_F(ChessBoardTest, Bitboard_Initialization) {
  EXPECT_EQ_BOARD(board.getPawns(White), rank2);
  EXPECT_EQ_BOARD(board.getPawns(Black), rank7);
  EXPECT_EQ_BOARD(board.getOccupied(), Bitboard(0xffff00000000ffff));
}

TEST_F(ChessBoardTest, GetPieces) {
  EXPECT_EQ_BOARD(board.getPawns(White), board.getPieceSet(WhitePawn));
  EXPECT_EQ_BOARD(board.getPawns(Black), board.getPieceSet(BlackPawn));

  EXPECT_EQ_BOARD(board.getKnights(White), board.getPieceSet(WhiteKnight));
  EXPECT_EQ_BOARD(board.getKnights(Black), board.getPieceSet(BlackKnight));

  EXPECT_EQ_BOARD(board.getBishops(White), board.getPieceSet(WhiteBishop));
  EXPECT_EQ_BOARD(board.getBishops(Black), board.getPieceSet(BlackBishop));

  EXPECT_EQ_BOARD(board.getRooks(White), board.getPieceSet(WhiteRook));
  EXPECT_EQ_BOARD(board.getRooks(Black), board.getPieceSet(BlackRook));

  EXPECT_EQ_BOARD(board.getQueens(White), board.getPieceSet(WhiteQueen));
  EXPECT_EQ_BOARD(board.getQueens(Black), board.getPieceSet(BlackQueen));

  EXPECT_EQ_BOARD(board.getKings(White), board.getPieceSet(WhiteKing));
  EXPECT_EQ_BOARD(board.getKings(Black), board.getPieceSet(BlackKing));
}

// =====================================
// Board movement
// =====================================
TEST_F(ChessBoardTest, NortOne) {
  EXPECT_EQ_BOARD(board.nortOne(rank1), rank2);
  EXPECT_EQ_BOARD(board.nortOne(rank2), rank3);
  EXPECT_EQ_BOARD(board.nortOne(rank3), rank4);
  EXPECT_EQ_BOARD(board.nortOne(rank4), rank5);
  EXPECT_EQ_BOARD(board.nortOne(rank5), rank6);
  EXPECT_EQ_BOARD(board.nortOne(rank6), rank7);
  EXPECT_EQ_BOARD(board.nortOne(rank7), rank8);
  EXPECT_EQ_BOARD(board.nortOne(rank8), 0);
}

TEST_F(ChessBoardTest, SoutOne) {
  EXPECT_EQ_BOARD(board.soutOne(rank1), 0);
  EXPECT_EQ_BOARD(board.soutOne(rank2), rank1);
  EXPECT_EQ_BOARD(board.soutOne(rank3), rank2);
  EXPECT_EQ_BOARD(board.soutOne(rank4), rank3);
  EXPECT_EQ_BOARD(board.soutOne(rank5), rank4);
  EXPECT_EQ_BOARD(board.soutOne(rank6), rank5);
  EXPECT_EQ_BOARD(board.soutOne(rank7), rank6);
  EXPECT_EQ_BOARD(board.soutOne(rank8), rank7);
}

TEST_F(ChessBoardTest, EastOne) {
  EXPECT_EQ_BOARD(board.eastOne(aFile), bFile);
  EXPECT_EQ_BOARD(board.eastOne(bFile), cFile);
  EXPECT_EQ_BOARD(board.eastOne(cFile), dFile);
  EXPECT_EQ_BOARD(board.eastOne(dFile), eFile);
  EXPECT_EQ_BOARD(board.eastOne(eFile), fFile);
  EXPECT_EQ_BOARD(board.eastOne(fFile), gFile);
  EXPECT_EQ_BOARD(board.eastOne(gFile), hFile);
  EXPECT_EQ_BOARD(board.eastOne(hFile), 0);
}

TEST_F(ChessBoardTest, WestOne) {
  EXPECT_EQ_BOARD(board.westOne(aFile), 0);
  EXPECT_EQ_BOARD(board.westOne(bFile), aFile);
  EXPECT_EQ_BOARD(board.westOne(cFile), bFile);
  EXPECT_EQ_BOARD(board.westOne(dFile), cFile);
  EXPECT_EQ_BOARD(board.westOne(eFile), dFile);
  EXPECT_EQ_BOARD(board.westOne(fFile), eFile);
  EXPECT_EQ_BOARD(board.westOne(gFile), fFile);
  EXPECT_EQ_BOARD(board.westOne(hFile), gFile);
}
TEST_F(ChessBoardTest, NoEastOne) {
  auto origin = CBB(1) << a1;
  EXPECT_EQ_BOARD(board.noEaOne(origin), board.nortOne(board.eastOne(origin)));
  EXPECT_EQ_BOARD(board.noEaOne(origin), CBB(1) << b2);
  EXPECT_EQ_BOARD(board.noEaOne(h1A8Diag), 0x408102040800000);
}
TEST_F(ChessBoardTest, SoEastOne) {
  auto origin = CBB(1) << a8;
  EXPECT_EQ_BOARD(board.soEaOne(origin), board.soutOne(board.eastOne(origin)));
  EXPECT_EQ_BOARD(board.soEaOne(origin), CBB(1) << b7);
  EXPECT_EQ_BOARD(board.soEaOne(h1A8Diag), 0x2040810204080);
}
TEST_F(ChessBoardTest, NoWestOne) {
  auto origin = CBB(1) << h1;
  EXPECT_EQ_BOARD(board.noWeOne(origin), board.nortOne(board.westOne(origin)));
  EXPECT_EQ_BOARD(board.noWeOne(origin), CBB(1) << g2);
  EXPECT_EQ_BOARD(board.noWeOne(a1H8Diag), 0x2010080402010000)
      << board.printBitboard(0x2010080402010000);
}

// =====================================
// Pawn fills
// =====================================
TEST_F(ChessBoardTest, RearFill) {
  Bitboard in[8] = {
      CBB(1) << e5,
      CBB(1) << d5,
      (CBB(1) << e5) | (CBB(1) << d5),
      0,
  };
  board = ChessBoard(in);
  Bitboard empty = Bitboard(0);
  auto wfill = board.putPiece(
      board.putPiece(
          board.putPiece(board.putPiece(board.putPiece(empty, e1), e2), e3),
          e4),
      e5);
  EXPECT_EQ_BOARD(board.wRearFill(board.getPawns(White)), wfill);
  auto bfill = board.putPiece(
      board.putPiece(
          board.putPiece(board.putPiece(board.putPiece(empty, d1), d2), d3),
          d4),
      d5);
  EXPECT_EQ_BOARD(board.bRearFill(board.getPawns(Black)), bfill);
}

TEST_F(ChessBoardTest, FrontFill) {
  Bitboard in[8] = {
      CBB(1) << e5,
      CBB(1) << d5,
      (CBB(1) << e5) | (CBB(1) << d5),
      0,
  };
  board = ChessBoard(in);
  Bitboard empty = Bitboard(0);
  auto wfill = board.putPiece(
      board.putPiece(board.putPiece(board.putPiece(empty, e5), e6), e7), e8);
  EXPECT_EQ_BOARD(board.wFrontFill(board.getPawns(White)), wfill);
  auto bfill = board.putPiece(
      board.putPiece(board.putPiece(board.putPiece(empty, d5), d6), d7), d8);
  EXPECT_EQ_BOARD(board.wFrontFill(board.getPawns(Black)), bfill);
}

TEST_F(ChessBoardTest, PawnMove) {
  Move move = {a2, a4, Pawn, White, Empty, White, Empty};
  board.quiteMove(&move);
  EXPECT_EQ_BOARD(board.getPawns(White),
                  (rank2 ^ (CBB(1) << a2) ^ (CBB(1) << a4)));
}

TEST_F(ChessBoardTest, FileFill) {
  Bitboard in[8] = {
      CBB(1) << e5,
      CBB(1) << d5,
      (CBB(1) << e5) | (CBB(1) << d5),
      0,
  };
  board = ChessBoard(in);
  Bitboard empty = Bitboard(0);
  EXPECT_EQ_BOARD(board.fileFill(board.getOccupied()), (eFile | dFile));
}
