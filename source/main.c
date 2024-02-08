#include <time.h>
#include <string.h>
#include <stdio.h>
#include "raylib.h"
#include "Tetris.h"
#include "CheckCollision.h"

extern int stage[];
extern Color colorTypes[];
extern int *tetrominoTypes[7][4];
extern int totalScore;
extern int rowCounter;

extern Music background_music;
extern Music game_over_music;
extern Music *current_music;
extern Sound tetromino_moving_sound;
extern Sound tetromino_stomp_sound;
extern Sound collision_sound;
extern Sound rotation_sound;
extern Sound explosion_sound;

int main(int argc, char **argv, char **environ)
{
    const int windowWidth = WINDOW_WIDTH;
    const int windowHeight = WINDOW_HEIGHT;

    const int startOffsetX = (windowWidth / 2) - ((STAGE_WIDTH * TILE_SIZE) / 2);
    const int startOffsetY = (windowHeight / 2) - ((STAGE_HEIGHT * TILE_SIZE) / 2);

    const int tetrominoStartX = STAGE_WIDTH / 2;
    const int tetrominoStartY = 0;

    int currentTetrominoX = tetrominoStartX;
    int currentTetrominoY = tetrominoStartY;

    time_t unixTime;

    time(&unixTime);

    SetRandomSeed(unixTime);

    int currentTetrominoType = GetRandomValue(0, 6);
    int currentRotation = 0;

    const float moveTetrominoDownTimer = 1.f;
    float timeToMoveTetrominoDown = moveTetrominoDownTimer;
    int currentColor = GetRandomValue(0, 6);
    int game_over = 0;

    TraceLog(LOG_INFO, "Number of arguments : %d", argc);
    for (int i = 0; i < argc; i++)
    {
        TraceLog(LOG_INFO, "Argument : %d = %s", i, argv[i]);
    }
    while (*environ != 0)
    {
        TraceLog(LOG_INFO, "Argument : %s", *environ);
        environ++;
    }

    InitWindow(windowWidth, windowHeight, "AIV - Tetris");

    InitAudioDevice();
    SetMasterVolume(0.5f);

    background_music = LoadMusicStream("SFX/Background-Music.ogg");
    game_over_music = LoadMusicStream("SFX/game_over.ogg");
    current_music = &background_music;

    tetromino_moving_sound = LoadSound("SFX/move.ogg");
    tetromino_stomp_sound = LoadSound("SFX/Tetromino_stomp.ogg");
    collision_sound = LoadSound("SFX/collision.ogg");
    rotation_sound = LoadSound("SFX/rotate.wav");
    explosion_sound = LoadSound("SFX/explosion.ogg");

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {

        PlayMusicStream(*current_music);
        UpdateMusicStream(*current_music);
        timeToMoveTetrominoDown -= GetFrameTime();

        if (IsKeyPressed(KEY_SPACE))
        {
            const int lastRotation = currentRotation;

            currentRotation++;

            if (currentRotation > 3)
            {
                currentRotation = 0;
            }

            if (CheckCollision(currentTetrominoX, currentTetrominoY, tetrominoTypes[currentTetrominoType][currentRotation]))
            {
                currentRotation = lastRotation;
            }

            PlaySound(rotation_sound);
        }
        if (IsKeyPressed(KEY_RIGHT))
        {
            // No need to check overflow, wall is your protector
            if (!CheckCollision(currentTetrominoX + 1, currentTetrominoY, tetrominoTypes[currentTetrominoType][currentRotation]))
            {
                currentTetrominoX++;
                PlaySound(tetromino_moving_sound);
            }
            else
            {
                PlaySound(collision_sound);
            }
        }
        if (IsKeyPressed(KEY_LEFT))
        {
            // No need to check overflow, wall is your protector
            if (!CheckCollision(currentTetrominoX - 1, currentTetrominoY, tetrominoTypes[currentTetrominoType][currentRotation]))
            {
                currentTetrominoX--;
                PlaySound(tetromino_moving_sound);
            }
            else
            {
                PlaySound(collision_sound);
            }
        }
        if (timeToMoveTetrominoDown <= 0 || IsKeyDown(KEY_DOWN))
        {
            if (!CheckCollision(currentTetrominoX, currentTetrominoY + 1, tetrominoTypes[currentTetrominoType][currentRotation]))
            {
                if (IsKeyDown(KEY_DOWN))
                {
                    totalScore += 1;
                }

                currentTetrominoY++;

                if (rowCounter < 25)
                {
                    timeToMoveTetrominoDown = moveTetrominoDownTimer;
                }
                else if (rowCounter >= 25 && rowCounter < 50)
                {
                    timeToMoveTetrominoDown = 0.8f;
                }
                else if (rowCounter >= 50 && rowCounter < 75)
                {
                    timeToMoveTetrominoDown = 0.6f;
                }
                else if (rowCounter >= 75 && rowCounter < 100)
                {
                    timeToMoveTetrominoDown = 0.4f;
                }
                else if (rowCounter >= 100)
                {
                    timeToMoveTetrominoDown = 0.2f;
                }
            }
            else
            {
                for (int y = 0; y < TETROMINO_SIZE; y++)
                {
                    for (int x = 0; x < TETROMINO_SIZE; x++)
                    {
                        const int offset = y * TETROMINO_SIZE + x;

                        const int *tetromino = tetrominoTypes[currentTetrominoType][currentRotation];

                        if (tetromino[offset] == 1)
                        {
                            const int offset_stage = (y + currentTetrominoY) * STAGE_WIDTH + (x + currentTetrominoX);
                            stage[offset_stage] = currentColor + 1;
                            PlaySound(tetromino_stomp_sound);
                        }
                    }
                }

                for (int i = 0; i < 5; i++)
                {
                    DeleteLines();
                }

                currentTetrominoX = tetrominoStartX;
                currentTetrominoY = tetrominoStartY;

                currentTetrominoType = GetRandomValue(0, 6);
                currentRotation = 0;
                currentColor = GetRandomValue(0, 7);
            }
        }

        BeginDrawing();
        GetFontDefault();
        DrawText(TextFormat("Score: %010i", totalScore), 50, 20, 20, RED);
        DrawText(TextFormat("Rows: %010i", rowCounter), 250, 20, 20, RED);
        ClearBackground(BLACK);

        for (int y = 0; y < STAGE_HEIGHT; y++)
        {
            for (int x = 0; x < STAGE_WIDTH; x++)
            {
                const int offset = y * STAGE_WIDTH + x;
                const int color = stage[offset];

                if (stage[offset] != 0)
                {
                    DrawRectangle(x * TILE_SIZE + (startOffsetX / 2), y * TILE_SIZE + startOffsetY, TILE_SIZE, TILE_SIZE, colorTypes[color - 1]);
                }

                DrawRectangleLines(x * TILE_SIZE + (startOffsetX / 2), y * TILE_SIZE + startOffsetY, TILE_SIZE, TILE_SIZE, DARKGRAY);
            }
        }

        if (CheckCollision(currentTetrominoX, 0, tetrominoTypes[currentTetrominoType][currentRotation]))
        {

            GameOver();
        }
        else
        {
            drawTetromino(colorTypes[currentColor], (startOffsetX / 2), startOffsetY, currentTetrominoX, currentTetrominoY, tetrominoTypes[currentTetrominoType][currentRotation]);
        }

        EndDrawing();
    }

    UnloadMusicStream(*current_music);
    UnloadSound(tetromino_moving_sound);
    UnloadSound(tetromino_stomp_sound);
    UnloadSound(rotation_sound);
    UnloadSound(collision_sound);
    UnloadSound(explosion_sound);
    CloseAudioDevice();
    CloseWindow();

    return 0;
}