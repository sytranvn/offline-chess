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

bool Game::MakeMove(Move move) {
  Piece *p = board->GetPiece(move.fromRow, move.fromCol);
  if (p == nullptr) {
    return false;
    // throw std::runtime_error("No piece at source");
  }
  if (p->IsWhite() != GetIsWhiteTurn()) {
    return false;
    // throw std::runtime_error("Not your turn");
  }
  if (!board->MovePiece(move)) {
    return false;
  }
  moves.push_back(move);
  std::cout << "Move " << moves.size() << " " << p->GetSymbol() << " "
            << (char)(move.fromCol + 'A') << move.fromRow + 1 << " to "
            << (char)(move.toCol + 'A') << move.toRow + 1 << std::endl;
  currentPlayer = GetIsWhiteTurn() ? black : white;
  return true;
}
