#include "UpdateLogic.h"


void Update()
{
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
                    DrawRectangle(x * TILE_SIZE + (STAGE_OFFSETX / 2), y * TILE_SIZE + STAGE_OFFSETY, TILE_SIZE, TILE_SIZE, colorTypes[color - 1]);
                }

                DrawRectangleLines(x * TILE_SIZE + (STAGE_OFFSETX / 2), y * TILE_SIZE + STAGE_OFFSETY, TILE_SIZE, TILE_SIZE, DARKGRAY);
            }
        }

        if (CheckCollision(currentTetrominoX, 0, tetrominoTypes[currentTetrominoType][currentRotation]))
        {

            GameOver();
        }
        else
        {
            drawTetromino(colorTypes[currentColor], (STAGE_OFFSETX / 2), STAGE_OFFSETY, currentTetrominoX, currentTetrominoY, tetrominoTypes[currentTetrominoType][currentRotation]);
        }

        EndDrawing();
    }
}