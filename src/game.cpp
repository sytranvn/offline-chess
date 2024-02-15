#include "game.h"

Game::Game() {
  board = new Board();
  white = new Player(true);
  black = new Player(false);
  currentPlayer = white;
}

Board *Game::GetBoard() { return board; }

bool Game::IsGameOver() const { return false; }

void Game::AddMove(Move move) {
  moves.push_back(move);
  currentMove = moves.size() - 1;
};
void Game::Forward() {
  if (currentMove < moves.size() - 1)
    currentMove++;
};
void Game::Back() {
  if (currentMove > 0)
    currentMove--;
};
bool Game::GetIsBlackTurn() { return currentPlayer == black; }
bool Game::GetIsWhiteTurn() { return currentPlayer == white; }

void Game::MakeMove(Move move) {
  Piece *p = board->GetPiece(move.fromRow, move.fromCol);
  if (p == nullptr) {
    throw std::runtime_error("No piece at source");
  }
  if (p->IsWhite() != GetIsWhiteTurn()) {
    throw std::runtime_error("Not your turn");
  }
  board->MovePiece(move);
  moves.push_back(move);
  std::cout << "Move " << moves.size() << " " << p->GetSymbol() << " "
            << (char)(move.fromCol + 'A') << move.fromRow + 1 << " to "
            << (char)(move.toY + 'A') << move.toX + 1 << std::endl;
  currentPlayer = GetIsWhiteTurn() ? black : white;
}
