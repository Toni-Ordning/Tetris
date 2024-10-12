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
    return tiles.at(get_index(x, y));
}

void playfield::set_tile(int x, int y, const Color& color)
{
    tiles.at(get_index(x, y)) = tile{color, true};
}

void playfield::clear_line(int y)
{
    for (int x = 0; x < width; ++x)
    {
        tiles.at(get_index(x, y)) = tile{light_white, false};
    }

    move_lines_down(y - 1);
}

void playfield::move_lines_down(int y)
{
    if (y >= height - 1)
    {
        return;
    }

    for (int yy = y; yy > 0; --yy)
    {
        move_line_down(yy);
    }
}

void playfield::move_line_down(int y)
{
    for (int x = 0; x < width; ++x)
    {
        move_tile_down(x, y);
    }
}

bool playfield::move_tile_down(int x, int y)
{
    int new_index = get_index(x, y + 1);
    if (tiles.at(new_index).has_shape)
    {
        return false;
    }

    int old_index = get_index(x, y);
    tiles.at(new_index) = tiles.at(old_index);
    tiles.at(old_index) = tile{light_white, false};
    return true;
}

int playfield::get_index(int x, int y) const
{
    int index = y * width + x;
    assert(index < tiles.size());
    return index;
}
