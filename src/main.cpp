#include "raylib.h"

#include "constants.h"
#include "renderer.h"
#include "tetris.h"

int main()
{
    InitWindow(window_width, window_height, "Tetris");
    SetTargetFPS(60);

    tetris tetris(10, 20);
    renderer renderer(tetris);

    while (!WindowShouldClose())
    {
        tetris.tick();

        BeginDrawing();

        ClearBackground(game_background);
        renderer.draw();

        EndDrawing();
    }

    CloseWindow();
}
