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
    int index = get_index(x, y);
    assert(index < tiles.size());
    tiles.at(index) = tile{color, true};
}

void playfield::clear_line(int y)
{
    for (int x = 0; x < width; ++x)
    {
        tiles.at(get_index(x, y)) = tile{light_white, false};
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

            int old_index = get_index(yy - 1, x);
            int new_index = get_index(yy, x);
            tiles.at(new_index) = tiles.at(old_index);
            tiles.at(old_index) = tile{light_white, false};
        }
    }
}

int playfield::get_index(int x, int y)
{
    return y * width + x;
}
