#include "board.h"
#include "game.h"
#include "raylib.h"
#include "timer.h"
#include <fstream>
#include <vector>

#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
#endif

//----------------------------------------------------------------------------------
// Global Variables Definition
//----------------------------------------------------------------------------------
int screenWidth = 800;
int screenHeight = 800;
int padding = 40;
Move *currentMove = nullptr;
std::vector<Move> moves;

Game *game = new Game();
Board *board = game->GetBoard();
Timer timer = {0};
Spot *selectedSpot = nullptr;

Texture2D piecesTexture = {0};

//----------------------------------------------------------------------------------
// Module Functions Declaration
//----------------------------------------------------------------------------------
void UpdateDrawFrame(void); // Update and Draw one frame
//----------------------------------------------------------------------------------
// Game functions
bool MovesEnded();
void GetMoves(std::vector<Move> &moves);
void DrawBoardAndPieces(Board *board);
void Replay(const std::vector<Move> &moves);
//----------------------------------------------------------------------------------
// Main Entry Point
//----------------------------------------------------------------------------------
int main() {
  // Initialization
  //--------------------------------------------------------------------------------------
  GetMoves(moves);
  InitWindow(screenWidth + padding, screenHeight + padding, "Chess offline");
  std::cout << "Moves size: " << moves.size() << std::endl;
  // Load resources
  piecesTexture = LoadTexture("resources/images/pieces.png");

#if defined(PLATFORM_WEB)
  emscripten_set_main_loop(UpdateDrawFrame, 0, 1);
#else
  SetTargetFPS(60); // Set our game to run at 60 frames-per-second
  //--------------------------------------------------------------------------------------

  // Main game loop
  while (!WindowShouldClose()) // Detect window close button or ESC key
  {
    UpdateDrawFrame();
  }
#endif

  UnloadTexture(piecesTexture);

  // De-Initialization
  //--------------------------------------------------------------------------------------
  CloseWindow(); // Close window and OpenGL context
  //--------------------------------------------------------------------------------------

  delete board;
  return 0;
}

void UpdateDrawFrame(void) {
  // Update
  //----------------------------------------------------------------------------------
  BeginDrawing();
  ClearBackground(RAYWHITE);
  //
  if (!game->IsGameOver()) {
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
      std::cout << "Mouse button pressed" << std::endl;
      Vector2 spotPosition = GetMousePosition();
      if (selectedSpot == nullptr) {
        int col = ((int)spotPosition.x - padding) / (screenWidth / 8);
        int row = ((int)spotPosition.y - padding) / (screenHeight / 8);
        if (board->GetPiece(row, col) != nullptr)
          selectedSpot = board->GetSpot(row, col);
      } else {
        int col = ((int)spotPosition.x - padding) / (screenWidth / 8);
        int row = ((int)spotPosition.y - padding) / (screenHeight / 8);
        auto to = board->GetSpot(row, col);
        if (to == selectedSpot) {
          selectedSpot = nullptr;
        } else if (selectedSpot->GetPiece() != nullptr) {
          Move move = {selectedSpot->GetRow(), selectedSpot->GetCol(), row,
                       col};
          try {
            game->MakeMove(move);
            std::cout << board->ToString();
            currentMove = &move;
          } catch (std::exception &e) {
            std::cerr << e.what() << std::endl;
            currentMove = nullptr;
          }
        }
        selectedSpot = nullptr;
      }
    }
  }
  DrawBoardAndPieces(board);
  EndDrawing();
}

// bool MovesEnded() { return currentMove == 10; }

void GetMoves(std::vector<Move> &moves) {
  std::ifstream file("resources/games/moves.txt");
  if (!file)
    std::cout << "Error opening file resources/games/moves.txt" << std::endl;

  int fromX, fromY, toX, toY;
  int n;
  file >> n;
  while (n--) {
    file >> fromX >> fromY >> toX >> toY;
    std::cout << fromX << fromY << toX << toY << std::endl;
    moves.push_back({fromX, fromY, toX, toY});
  }
};

void DrawBoardAndPieces(Board *board) {
  int spotWidth = screenWidth / 8;
  int spotHeight = screenHeight / 8;
  // Draw board
  for (int i = 0; i < board->size; ++i) {
    for (int j = 0; j < board->size; ++j) {
      auto spot = board->GetSpot(i, j);
      Color color = spot->IsWhite() ? LIGHTGRAY : BROWN;
      if (currentMove) {
        bool moved = i == currentMove->fromRow && j == currentMove->fromCol;
        bool filled = i == currentMove->toX && j == currentMove->toY;
        if (moved || filled) {
          // color.r &= 0xff;
          color.r ^= 0x33;
          color.g ^= 0x33;
        }
      }
      if (spot == selectedSpot) {
        color.r ^= 0x33;
        color.g ^= 0x33;
        // color.b ^= 0x88;
      }
      DrawRectangle(padding + j * spotWidth, padding + i * spotHeight,
                    spotWidth, spotHeight, color);
      if (spot->GetPiece() != nullptr) {
        auto piece = spot->GetPiece();
        char s = piece->GetSymbol();
        // DrawText(TextFormat("%c", s),
        //          padding + j * spotHeight + spotHeight / 2 - 10,
        //          padding + i * spotWidth + spotWidth / 2 - 10, 20,
        //          piece->IsWhite() ? RED : BLUE);
        Rectangle source = {10, 0, 300, 400};
        if (piece->IsWhite()) {
          source.y = 400;
        }
        switch (piece->GetSymbol()) {
        case 'R':
        case 'r':
          source.x = 0;
          break;
        case 'B':
        case 'b':
          source.x = 300;
          break;
        case 'Q':
        case 'q':
          source.x = 600;
          break;
        case 'K':
        case 'k':
          source.x = 900;
          break;
        case 'N':
        case 'n':
          source.x = 1200;
          break;
        case 'P':
        case 'p':
          source.x = 1500;
          break;
        }
        DrawTexturePro(
            piecesTexture, source,
            (Rectangle){(float)padding + j * spotHeight + (float)spotHeight / 2,
                        (float)padding + i * spotWidth + (float)spotWidth / 2,
                        (float)spotHeight / 4 * 3, (float)spotWidth / 4 * 4},
            (Vector2){(float)spotHeight / 2 + 5, (float)spotWidth / 2 + 5},
            0.0f, WHITE);
      }
    }
  }
  for (int i = 0; i < board->size; ++i) {
    DrawText(TextFormat("%c", 'a' + i), padding + i * spotWidth + spotWidth / 2,
             padding / 2, 20, BLACK);
    DrawText(TextFormat("%d", 1 + i), padding / 2,
             padding + i * spotHeight + spotHeight / 2, 20, BLACK);
  }
}

// void Replay(const std::vector<Move> &moves) {
//   if (!TimerIsDone(&timer)) {
//     TimerUpdate(&timer);
//   } else {
//     auto move = moves[currentMove];
//     try {
//       game->MakeMove(move);
//       std::cout << board->ToString();
//     } catch (std::exception &e) {
//       std::cerr << e.what() << std::endl;
//     }
//     if (moves.size() > currentMove + 1)
//       currentMove++;
//     TimerStart(&timer, 2);
//   }
// }
