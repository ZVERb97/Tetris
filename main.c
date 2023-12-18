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

Music background_music;
extern Sound tetromino_sound;
extern Sound collision_sound;
extern Sound rotation_sound;
extern Sound explosion_sound;

int main(int argc, char** argv, char** environ)
{
    const int windowWidth = 500; 
    const int windowHeight = 700; 

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

    TraceLog(LOG_INFO, "Number of arguments : %d", argc);
    for(int i = 0; i < argc; i++)
    {
        TraceLog(LOG_INFO, "Argument : %d = %s", i, argv[i]);
    }
    while(*environ != 0)
    {
        TraceLog(LOG_INFO, "Argument : %s", *environ);
        environ++;
    }

    InitWindow(windowWidth, windowHeight, "Title");

    InitAudioDevice();
    SetMasterVolume(0.5f);
    
    background_music = LoadMusicStream("SFX/Background-Music.ogg");
    PlayMusicStream(background_music);

    tetromino_sound = LoadSound("SFX/move.ogg");
    collision_sound = LoadSound("SFX/collision.ogg");
    rotation_sound = LoadSound("SFX/rotate.wav");
    explosion_sound = LoadSound("SFX/explosion.ogg");
  

    SetTargetFPS(60);

    while(!WindowShouldClose())
    {
        UpdateMusicStream(background_music);
        timeToMoveTetrominoDown -= GetFrameTime();

        if (IsKeyPressed(KEY_SPACE))
        {
            const int lastRotation = currentRotation;

            currentRotation++;

            if (currentRotation > 3)
            {
                currentRotation = 0;
            }

            if (CheckCollision(currentTetrominoX,currentTetrominoY,tetrominoTypes[currentTetrominoType][currentRotation]))
            {
                currentRotation = lastRotation;
            }

            PlaySound(rotation_sound);
        }
        if (IsKeyPressed(KEY_RIGHT))
        {
            // No need to check overflow, wall is your protector
            if (!CheckCollision(currentTetrominoX+1,currentTetrominoY,tetrominoTypes[currentTetrominoType][currentRotation]))
            {
                currentTetrominoX++;
                PlaySound(tetromino_sound);
            }
            else
            {
                PlaySound(collision_sound);
            }
        }
        if (IsKeyPressed(KEY_LEFT))
        {
            // No need to check overflow, wall is your protector
            if (!CheckCollision(currentTetrominoX-1,currentTetrominoY,tetrominoTypes[currentTetrominoType][currentRotation]))
            {
                currentTetrominoX--;
                PlaySound(tetromino_sound);
            }
            else
            {
                PlaySound(collision_sound);
            }
        }
        if(timeToMoveTetrominoDown <= 0 || IsKeyDown(KEY_DOWN))
        {            
            if(!CheckCollision(currentTetrominoX,currentTetrominoY+1,tetrominoTypes[currentTetrominoType][currentRotation]))
            {
                currentTetrominoY++;
                timeToMoveTetrominoDown = moveTetrominoDownTimer;
            }
            else
            {
                for(int y = 0; y < TETROMINO_SIZE; y++)
                {
                    for(int x = 0; x < TETROMINO_SIZE; x++)
                    {
                        const int offset = y * TETROMINO_SIZE + x;

                        const int *tetromino = tetrominoTypes[currentTetrominoType][currentRotation];

                        if(tetromino[offset] == 1)
                        {
                            const int offset_stage = (y + currentTetrominoY) * STAGE_WIDTH + (x + currentTetrominoX);
                            stage[offset_stage] = currentColor+1;

                        }
                    }
                }

                DeleteLines();
                
                currentTetrominoX = tetrominoStartX;
                currentTetrominoY = tetrominoStartY;

                currentTetrominoType = GetRandomValue(0, 6);
                currentRotation = 0;
                currentColor = GetRandomValue(0, 7);
            }
        }
        
        BeginDrawing();
        GetFontDefault();
        DrawText(TextFormat("Score: %010i",totalScore),50, 20,20,RED);
        DrawText(TextFormat("Rows: %010i",rowCounter),250,20,20,RED);
        ClearBackground(BLACK);

        for(int y = 0; y < STAGE_HEIGHT; y++)
        {
            for(int x = 0; x < STAGE_WIDTH; x++)
            {
                const int offset = y * STAGE_WIDTH + x;
                const int color = stage[offset];

                if(stage[offset] != 0)
                {
                    DrawRectangle(x * TILE_SIZE + (startOffsetX /2), y * TILE_SIZE + startOffsetY, TILE_SIZE, TILE_SIZE, colorTypes[color - 1]);
                }

                DrawRectangleLines(x * TILE_SIZE + (startOffsetX /2), y * TILE_SIZE + startOffsetY, TILE_SIZE, TILE_SIZE, DARKGRAY);
            }
        }
        
        if(CheckCollision(currentTetrominoX,0,tetrominoTypes[currentTetrominoType][currentRotation]))
        {
            printf("GAME OVER");
        }
        else
        {
            drawTetromino(colorTypes[currentColor],(startOffsetX /2), startOffsetY, currentTetrominoX, currentTetrominoY, tetrominoTypes[currentTetrominoType][currentRotation]);
        }
        
        EndDrawing();
        
    }

    UnloadMusicStream(background_music);
    UnloadSound(tetromino_sound);
    CloseAudioDevice();

    return 0;
}