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
