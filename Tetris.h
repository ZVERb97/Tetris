#include "raylib.h"

#define STAGE_WIDTH 12
#define STAGE_HEIGHT 22
#define TILE_SIZE 24
#define TETROMINO_SIZE 4
#define STAGE_OFFSETX ((500 / 2) - ((STAGE_WIDTH * TILE_SIZE) / 2)) 
#define STAGE_OFFSETY (700 / 2) - ((STAGE_HEIGHT * TILE_SIZE) / 2)

void drawTetromino(const Color currentColor, const int startOffsetX, const int startOffsetY, const int tetrominoStartX, const int tetrominoStartY, const int *tetromino);
void DeleteLines();
void ResetLines(int startLineY);