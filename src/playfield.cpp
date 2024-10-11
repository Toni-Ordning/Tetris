#include "playfield.h"

#include <cassert>

playfield::playfield(int width, int height)
    : width{width}
    , height{height}
{
    tiles.reserve(width * height);
    for (std::size_t i = 0; i < width * height; ++i)
    {
        tiles.push_back(tile{});
    }
}

int playfield::get_width() const noexcept
{
    return width; 
}

int playfield::get_height() const noexcept
{
    return height;
}

const tile& playfield::get_tile(int x, int y) const
{
    int index = y * width + x;
    assert(index < tiles.size());
    return tiles.at(index);
}

void playfield::set_tile(int x, int y, const Color& color)
{
    int index = y * width + x;
    tiles.at(index) = tile{color, true};
}

void playfield::clear_line(int y)
{
    for (int x = 0; x < width; ++x)
    {
        int index = y * width + x;
        tiles.at(index) = tile{light_white, false};
    }
}

void playfield::move_lines_down(int y)
{
    for (int yy = y; yy > 0; --yy)
    {
        for (int x = 0; x < width; ++x)
        {
            if (yy == 0)
            {
                break;
            }

            int old_index = (yy - 1) * width + x;
            int new_index = yy * width + x;
            tiles.at(new_index) = tiles.at(old_index);
            tiles.at(old_index) = tile{light_white, false};
        }
    }
}
