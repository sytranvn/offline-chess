#include "spot.h"

Spot::Spot(int row, int col, Piece *piece, bool isWhite, Board *board)
    : row(row), col(col), piece(piece), isWhite(isWhite), board(board){};
Piece *Spot::GetPiece() { return piece; }
void Spot::SetPiece(Piece *p) { piece = p; }

int Spot::GetCol() { return col; }
int Spot::GetRow() { return row; }
