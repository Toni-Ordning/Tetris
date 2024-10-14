#include "raylib.h"
#include "raygui.h"

#include "constants.h"
#include "input.h"
#include "renderer.h"
#include "tetris.h"

#include <functional>
#include <map>

struct game_context
{
    tetris& game;
    renderer& ren;
};

static void game_over(const game_context& context);
static void game_running(const game_context& context);

std::map<game_state, std::function<void(game_context)>> main_loop
{
    {game_state::over, game_over},
    {game_state::running, game_running},
};

int main()
{
    InitWindow(window_width, window_height, "Tetris");
    SetTargetFPS(60);

    tetris tetris(10, 20);
    renderer renderer(tetris);
    game_context context{tetris, renderer};

    while (!WindowShouldClose())
    {
        std::function<void(game_context)> loop = main_loop.at(tetris.state);
        loop(context);
    }

    if (IsWindowReady())
    {
        CloseWindow();
    }
}

static void game_over(const game_context& context)
{
    BeginDrawing();

    ClearBackground(game_background);

    const float button_distance = 140;
    float y = 100;
    std::string level_text = "Level: " + std::to_string(context.game.get_level());
    std::string score_text = "Score: " + std::to_string(context.game.get_score());
    std::string label_text = level_text + "\n" + score_text;
    GuiLabel(Rectangle{window_width / 2 - 50, y, 100, 100}, label_text.c_str());

    y += button_distance;
    if (GuiButton(Rectangle{window_width / 2 - 50, y, 100, 100}, "Restart"))
    {
        context.game = tetris(10, 20);
        context.game.state = game_state::running;
    }

    y += button_distance;
    if (GuiButton(Rectangle{window_width / 2 - 50, y, 100, 100}, "Quit"))
    {
        CloseWindow();
        return;
    }

    EndDrawing();
}

static void game_running(const game_context& context)
{
    context.game.tick();

    std::deque<input_event> input_events = get_input_events();
    context.game.process_events(input_events);

    BeginDrawing();

    ClearBackground(game_background);
    context.ren.draw();

    EndDrawing();
}
