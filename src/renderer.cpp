#include "renderer.h"

#include "raylib.h"

#include "constants.h"

#include <cassert>
#include <cmath>

renderer::renderer(const tetris& game)
    : game{game}
{
}

void renderer::draw()
{
    int tile_size = std::lround(window_height / game.get_height());
    int draw_position = std::lround(window_width / 3);

    for (int y = 0; y < game.get_height(); ++y)
    {
        for (int x = 0; x < game.get_width(); ++x)
        {
            int index = y * game.get_width() + x;
            assert(index < game.get_height() * game.get_width());

            const tile& t = game.get_tile(x, y);

            DrawRectangle(draw_position + x * tile_size, y * tile_size, tile_size, tile_size, t.color);
            DrawRectangleLines(draw_position + x * tile_size, y * tile_size, tile_size, tile_size, game_background);
        }
    }

    if (std::optional<piece> piece = game.get_piece())
    {
        piece->draw(draw_position, tile_size, piece->get_color(), game_background);
    }
}
