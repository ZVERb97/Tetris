#ifndef TETRIS_H
#define TETRIS_H
#include "raylib.h"

#define STAGE_WIDTH 12
#define STAGE_HEIGHT 22
#define WINDOW_WIDTH 500
#define WINDOW_HEIGHT 700
#define TILE_SIZE 24
#define TETROMINO_SIZE 4
#define STAGE_OFFSETX ((WINDOW_WIDTH / 2) - ((STAGE_WIDTH * TILE_SIZE) / 2)) 
#define STAGE_OFFSETY ((WINDOW_HEIGHT / 2)) - ((STAGE_HEIGHT * TILE_SIZE) / 2)

extern const int scorePoint;
extern int totalScore;
extern int rowCounter;
extern const int delete_time;
extern int delete_time_temp;
extern int stage[];
extern const Color colorTypes[];
extern const int *tetrominoTypes[7][4];
extern const int tetrominoStartX;
extern const int tetrominoStartY;
extern int currentTetrominoX;
extern int currentTetrominoY;
extern int currentTetrominoType;
extern int currentRotation;
extern int currentColor;
extern const float moveTetrominoDownTimer;
extern float timeToMoveTetrominoDown;

extern Music background_music;
extern Music game_over_music;
extern Music *current_music;
extern Sound tetromino_moving_sound;
extern Sound tetromino_stomp_sound;
extern Sound collision_sound;
extern Sound rotation_sound;
extern Sound explosion_sound;

void InitializeGame();
void drawTetromino(const Color currentColor, const int startOffsetX, const int startOffsetY, const int tetrominoStartX, const int tetrominoStartY, const int *tetromino);
void DeleteLines();
void ResetLines(int startLineY);
void GameOver();

#endif