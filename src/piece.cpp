#include "piece.h"

#include "constants.h"

#include <cassert>

piece::piece(piece_type type)
{
    build_piece(type);

    assert(width != 0);
    assert(height != 0);
    assert(!blocks.empty());
}

void piece::build_piece(piece_type type)
{
    switch (type)
    {
        case piece_type::i:
            width = 4;
            height = 1;
            blocks = std::vector<bool>(width * height, false);
            x = 3;
            y = 0;
            set_block(0, 0);
            set_block(1, 0);
            set_block(2, 0);
            set_block(3, 0);
            break;
        case piece_type::j:
            width = 3;
            height = 2;
            blocks = std::vector<bool>(width * height, false);
            x = 3;
            y = 0;
            set_block(0, 0);
            set_block(0, 1);
            set_block(1, 1);
            set_block(2, 1);
            break;
        case piece_type::l:
            width = 3;
            height = 2;
            blocks = std::vector<bool>(width * height, false);
            x = 3;
            y = 0;
            set_block(2, 0);
            set_block(0, 1);
            set_block(1, 1);
            set_block(2, 1);
            break;
        case piece_type::o:
            width = 2;
            height = 2;
            blocks = std::vector<bool>(width * height, false);
            x = 4;
            y = 0;
            set_block(0, 0);
            set_block(0, 1);
            set_block(1, 0);
            set_block(1, 1);
            break;
        case piece_type::s:
            width = 3;
            height = 2;
            blocks = std::vector<bool>(width * height, false);
            x = 3;
            y = 0;
            set_block(1, 0);
            set_block(2, 0);
            set_block(0, 1);
            set_block(1, 1);
            break;
        case piece_type::z:
            width = 3;
            height = 2;
            blocks = std::vector<bool>(width * height, false);
            x = 3;
            y = 0;
            set_block(0, 0);
            set_block(1, 0);
            set_block(1, 1);
            set_block(2, 1);
            break;
        case piece_type::t:
            width = 3;
            height = 2;
            blocks = std::vector<bool>(width * height, false);
            x = 3;
            y = 0;
            set_block(1, 0);
            set_block(0, 1);
            set_block(1, 1);
            set_block(2, 1);
            break;
    }
}

int piece::get_x() const noexcept
{
    return x;
}

int piece::get_y() const noexcept
{
    return y;
}

int piece::get_width() const noexcept
{
    return width;
}

int piece::get_height() const noexcept
{
    return height;
}

void piece::set_block(int x, int y)
{
    int index = y * width + x;
    blocks.at(index) = true;
}

bool piece::get_block(int x, int y) const
{
    int index = y * width + x;
    return blocks.at(index);
}

Color piece::get_color() const
{
    return light_blue;
}

bool piece::can_move_down(const playfield& field)
{
    for (int y = height - 1; y >= 0; --y)
    {
        for (int x = 0; x < width; ++x)
        {
            if (!get_block(x, y))
            {
                continue;
            }

            if (this->y + y + 1 >= field.get_height())
            {
                return false;
            }

            if (field.get_tile(this->x + x, this->y + y + 1).has_shape)
            {
                return false;
            }
        }
    }

    return true;
}

void piece::move_down()
{
    y += 1;
}

void piece::move_left(const playfield& field)
{
    if (x == 0)
    {
        return;
    }

    for (int y = 0; y < height; ++y)
    {
        if (field.get_tile(x-1, y).has_shape)
        {
            return;
        }
    }

    --x;
}

void piece::move_right(const playfield& field)
{
    if (x + width >= field.get_width())
    {
        return;
    }

    for (int y = 0; y < height; ++y)
    {
        if (field.get_tile(x + width - 1, y).has_shape)
        {
            return;
        }
    }

    ++x;
}

void piece::draw(int field_position, int tile_size, const Color& tile_color, const Color& background)
{
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            int index = y * width + x;
            if (!blocks.at(index))
            {
                continue;
            }

            DrawRectangle(this->x*tile_size + field_position + x * tile_size, this->y*tile_size + y * tile_size, tile_size, tile_size, tile_color);
            DrawRectangleLines(this->x*tile_size + field_position + x * tile_size, this->y*tile_size + y * tile_size, tile_size, tile_size, background);
        }
    }
}
