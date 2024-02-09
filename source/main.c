#include "UpdateLogic.h"

int main(int argc, char **argv, char **environ)
{
    InitializeGame();
    Update();

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