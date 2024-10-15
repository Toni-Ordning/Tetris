#include "renderer.h"

#include "raylib.h"
#include "raygui.h"

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

    if (piece* piece = game.get_piece())
    {
        piece->draw(draw_position, tile_size, piece->get_color(), game_background);
    }

    if (piece* guide_piece = game.get_guide_piece())
    {
        Color color = guide_piece->get_color();
        color.a = 0x40;
        guide_piece->draw(draw_position, tile_size, color, game_background);
    }

    draw_bag();
    draw_sidebar();
}

void renderer::draw_bag()
{
    const std::deque<std::unique_ptr<piece>>& pieces = game.get_pieces();
    if (pieces.empty())
    {
        return;
    }

    int draw_position = std::lround(window_width * 2/3);
    int piece_count = pieces.size();
    float offset = 50;
    
    float height_for_piece = window_height / piece_count;
    float width_for_piece = (window_width * 1 / 3) - (offset * 2);
    float tile_size = std::min(height_for_piece / 4, width_for_piece / 4);

    int piece_pos = 0;
    for (const auto& piece : pieces)
    {
        for (int y = 0; y < piece->get_height(); ++y)
        {
            for (int x = 0; x < piece->get_width(); ++x)
            {
                if (!piece->get_block(x, y))
                {
                    continue;
                }

                int draw_x = std::lround(draw_position + offset + x * tile_size);
                int draw_y = std::lround(piece_pos * height_for_piece + y * tile_size);
                DrawRectangle(draw_x, draw_y, tile_size, tile_size, piece->get_color());
                DrawRectangleLines(draw_x, draw_y, tile_size, tile_size, game_background);
            }
        }
        
        ++piece_pos;
    }
}

void renderer::draw_sidebar()
{
    float rectangle_size = 100;
    float x_position = std::lround(window_width * 1/6 - rectangle_size/2);
    float y = window_height / 3 - rectangle_size / 2;
    
    std::string level_text = "Level: " + std::to_string(game.get_level());
    GuiLabel(Rectangle{x_position, y, rectangle_size, rectangle_size}, level_text.c_str());

    y = window_height * 2/3 - rectangle_size / 2;

    std::string score_text = "Score: " + std::to_string(game.get_score());
    GuiLabel(Rectangle{x_position, y, rectangle_size, rectangle_size}, score_text.c_str());
}
