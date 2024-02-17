#include "engine/board.h"
#include "raylib.h"
#include <assert.h>
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

Texture2D piecesTexture = {0};

//----------------------------------------------------------------------------------
// Module Functions Declaration
//----------------------------------------------------------------------------------
void UpdateDrawFrame(void); // Update and Draw one frame
//----------------------------------------------------------------------------------
// Game functions
void DrawBoardAndPieces(ChessBoard *board);
//----------------------------------------------------------------------------------
// Main Entry Point
//----------------------------------------------------------------------------------
int main() {
  ChessBoard board = ChessBoard();
  std::string v;

  TraceLog(LOG_INFO, "Board:\n%s", board.fillChar().c_str());
  return 0;
}

void Render() {

  // Initialization
  //--------------------------------------------------------------------------------------
  InitWindow(screenWidth + padding, screenHeight + padding, "Chess offline");
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
};
void UpdateDrawFrame(void) {
  // Update
  //----------------------------------------------------------------------------------
  BeginDrawing();
  ClearBackground(RAYWHITE);
  EndDrawing();
}
