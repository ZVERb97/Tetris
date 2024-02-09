#include "raylib.h"
#include "Tetris.h"
#include <time.h>
#include <string.h>
#include <stdio.h>

int stage[] = 
{
    8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8,
    8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8,
    8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8,
    8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8,
    8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8,
    8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8,
    8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8,
    8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8,
    8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8,
    8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8,
    8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8,
    8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8,
    8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8,
    8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8,
    8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8,
    8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8,
    8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8,
    8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8,
    8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8,
    8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8,
    8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8,
    8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
};

const int lTetromino0[] =
{
    0, 1, 0, 0,
    0, 1, 0, 0,
    0, 1, 1, 0,
    0, 0, 0, 0,
};

const int lTetromino90[] =
{
    0, 0, 0, 0,
    1, 1, 1, 0,
    1, 0, 0, 0,
    0, 0, 0, 0,
};

const int lTetromino180[] =
{
    1, 1, 0, 0,
    0, 1, 0, 0,
    0, 1, 0, 0,
    0, 0, 0, 0,
};

const int lTetromino270[] =
{
    0, 0, 1, 0,
    1, 1, 1, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
};

const int jTetromino0[] =
{
    0, 1, 0, 0,
    0, 1, 0, 0,
    1, 1, 0, 0,
    0, 0, 0, 0,
};

const int jTetromino90[] =
{
    1, 0, 0, 0,
    1, 1, 1, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
};

const int jTetromino180[] =
{
    0, 1, 1, 0,
    0, 1, 0, 0,
    0, 1, 0, 0,
    0, 0, 0, 0,
};

const int jTetromino270[] =
{
    0, 0, 0, 0,
    1, 1, 1, 0,
    0, 0, 1, 0,
    0, 0, 0, 0,
};

const int oTetromino[] =
{
    1, 1, 0, 0,
    1, 1, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
};

const int sTetromino0[] =
{
    0, 0, 0, 0,
    0, 1, 1, 0,
    1, 1, 0, 0,
    0, 0, 0, 0,
};

const int sTetromino90[] =
{
    1, 0, 0, 0,
    1, 1, 0, 0,
    0, 1, 0, 0,
    0, 0, 0, 0,
};

const int sTetromino180[] =
{
    0, 1, 1, 0,
    1, 1, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
};

const int sTetromino270[] =
{
    0, 1, 0, 0,
    0, 1, 1, 0,
    0, 0, 1, 0,
    0, 0, 0, 0,
};

const int tTetromino0[] =
{
    0, 0, 0, 0,
    1, 1, 1, 0,
    0, 1, 0, 0,
    0, 0, 0, 0,
};

const int tTetromino90[] =
{
    0, 1, 0, 0,
    1, 1, 0, 0,
    0, 1, 0, 0,
    0, 0, 0, 0,
};

const int tTetromino180[] =
{
    0, 1, 0, 0,
    1, 1, 1, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
};

const int tTetromino270[] =
{
    1, 0, 0, 0,
    1, 1, 0, 0,
    1, 0, 0, 0,
    0, 0, 0, 0,
};

const int iTetromino0[] =
{
    0, 1, 0, 0,
    0, 1, 0, 0,
    0, 1, 0, 0,
    0, 1, 0, 0,
};

const int iTetromino90[] =
{
    0, 0, 0, 0,
    1, 1, 1, 1,
    0, 0, 0, 0,
    0, 0, 0, 0,
};

const int iTetromino180[] =
{
    0, 1, 0, 0,
    0, 1, 0, 0,
    0, 1, 0, 0,
    0, 1, 0, 0,
};

const int iTetromino270[] =
{
    0, 0, 0, 0,
    1, 1, 1, 1,
    0, 0, 0, 0,
    0, 0, 0, 0,
};

const int zTetromino0[] =
{
    0, 0, 0, 0,
    1, 1, 0, 0,
    0, 1, 1, 0,
    0, 0, 0, 0,
};

const int zTetromino90[] =
{
    0, 1, 0, 0,
    1, 1, 0, 0,
    1, 0, 0, 0,
    0, 0, 0, 0,
};

const int zTetromino180[] =
{
    1, 1, 0, 0,
    0, 1, 1, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
};

const int zTetromino270[] =
{
    0, 0, 1, 0,
    0, 1, 1, 0,
    0, 1, 0, 0,
    0, 0, 0, 0,
};

const int *tetrominoTypes[7][4] =
{
    {zTetromino0, zTetromino90, zTetromino180, zTetromino270},
    {sTetromino0, sTetromino90, sTetromino180, sTetromino270},
    {tTetromino0, tTetromino90, tTetromino180, tTetromino270},
    {oTetromino, oTetromino, oTetromino, oTetromino},
    {iTetromino0, iTetromino90, iTetromino180, iTetromino270},
    {jTetromino0, jTetromino90, jTetromino180, jTetromino270},
    {lTetromino0, lTetromino90, lTetromino180, lTetromino270},
};

const Color colorTypes[9] =
{
    {255,255,85,255},
    {85,43,158,255},
    {56,255,85,255},
    {255,255,63,255},
    {255,42,85,255},
    {255,100,85,255},
    {97,5,85,255},
    {128,128,128,255},
    {85,45,63,255},
    
};

Music background_music;
Music game_over_music;
Music *current_music;
Sound tetromino_moving_sound;
Sound collision_sound;
Sound rotation_sound;
Sound explosion_sound;
Sound tetromino_stomp_sound;

const int tetrominoStartX = STAGE_WIDTH / 2;
const int tetrominoStartY = 0;
int currentTetrominoX;
int currentTetrominoY;
int currentTetrominoType;
int currentRotation;
int currentColor;
const float moveTetrominoDownTimer = 1.f;
float timeToMoveTetrominoDown;

const int scorePoint = 100;
int totalScore;
int rowCounter = 0;
const int delete_time = 10;
int delete_time_temp = 0;


void InitializeGame()
{

    currentTetrominoX = tetrominoStartX;
    currentTetrominoY = tetrominoStartY;

    time_t unixTime;

    time(&unixTime);

    SetRandomSeed(unixTime);

    currentTetrominoType = GetRandomValue(0, 6);
    currentRotation = 0;

    timeToMoveTetrominoDown = moveTetrominoDownTimer;
    int currentColor = GetRandomValue(0, 6);
    int game_over = 0;

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "AIV - Tetris");

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
}

void drawTetromino(const Color currentColor, const int startOffsetX, const int startOffsetY, const int tetrominoStartX, const int tetrominoStartY, const int *tetromino)
{
    for(int y = 0; y < TETROMINO_SIZE; y++)
    {
        for(int x = 0; x < TETROMINO_SIZE; x++)
        {
            const int offset = y * TETROMINO_SIZE + x;

            if(tetromino[offset] == 1)
            {
                DrawRectangle((x + tetrominoStartX) * TILE_SIZE + startOffsetX, (y + tetrominoStartY) * TILE_SIZE + startOffsetY, TILE_SIZE, TILE_SIZE, currentColor);
                
            }
        }
    }
}

void ResetLines(int startLineY)
{

    for (int y = startLineY; y >= 0; y--)
    {
        for (int x = 1; x < STAGE_WIDTH - 1; x++)
        {
            const int offset = y * STAGE_WIDTH + x;
            const int offset_below = (y+1) * STAGE_WIDTH + x;

            if (stage[offset_below] == 0 && stage[offset] > 0)
            {
                stage[offset_below] = stage[offset];
                stage[offset] = 0;
            }
        }
    }   

    totalScore += scorePoint;
}

void DeleteLines()
{
    delete_time_temp = delete_time;

    for (int y = 0; y < STAGE_HEIGHT - 1; y++)
    {
        int checkLine = 1;

        for (int x = 1; x < STAGE_WIDTH - 1; x++)
        {
            const int offset = y * STAGE_WIDTH + x;

            if (stage[offset] == 0)
            {
                checkLine = 0;
                break;
            }
        }

        if(checkLine)
        {
            const int offset = y * STAGE_WIDTH + 1;
            int red_white_line = 1;
            do
            {   
                int offsetX = STAGE_OFFSETX / 2;
                BeginDrawing();
                if(red_white_line)
                {
                    DrawRectangle(offsetX,STAGE_OFFSETY + (y * TILE_SIZE),(STAGE_WIDTH * TILE_SIZE),TILE_SIZE,WHITE);
                    red_white_line = 0;
                }else
                {
                    DrawRectangle(offsetX,STAGE_OFFSETY + (y * TILE_SIZE),(STAGE_WIDTH * TILE_SIZE),TILE_SIZE,RED);
                    red_white_line = 1;
                }
                
                EndDrawing();
                delete_time_temp -= GetFrameTime();
                
               
            }while(delete_time_temp > 0);

            PlaySound(explosion_sound);
            memset(stage+offset,0,(STAGE_WIDTH-2)* sizeof(int));
            rowCounter++;
            delete_time_temp = delete_time;
            ResetLines(y);
        }
    }   
}

void GameOver()
{
    current_music = &game_over_music;

    DrawRectangle(0,0,WINDOW_WIDTH,WINDOW_HEIGHT,RED);
    DrawText("GAME OVER\n",100 ,(WINDOW_HEIGHT/2) - 50,50,BLACK);
    DrawText("Press ESC to exit the Game",50,WINDOW_HEIGHT/2,30,BLACK);
    DrawText(TextFormat("Score: %010i",totalScore),120, (WINDOW_HEIGHT/2) + 50,30,BLACK);
    DrawText(TextFormat("Rows: %010i",rowCounter),120,(WINDOW_HEIGHT/2) + 100,30,BLACK);
    StopSound(tetromino_moving_sound);
    StopSound(tetromino_stomp_sound);
    StopSound(rotation_sound);
    StopSound(collision_sound);

}
