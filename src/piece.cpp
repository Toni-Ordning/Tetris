#include "piece.h"

#include "constants.h"
#include "pieces.h"

std::unique_ptr<piece> build_piece(piece::piece_type type)
{
    switch (type)
    {
        case piece::piece_type::i:
            return std::make_unique<i_piece>();
        case piece::piece_type::j:
            return std::make_unique<j_piece>();
        case piece::piece_type::l:
            return std::make_unique<l_piece>();
        case piece::piece_type::o:
            return std::make_unique<o_piece>();
        case piece::piece_type::s:
            return std::make_unique<s_piece>();
        case piece::piece_type::z:
            return std::make_unique<z_piece>();
        case piece::piece_type::t:
            return std::make_unique<t_piece>();
        default:
            throw "Constructing unknown piece type!";
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
    return color;
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
        if (field.get_tile(x-1, this->y + y).has_shape)
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
        int index = y * width + width - 1;
        if (!blocks.at(index))
        {
            continue;
        }

        if (field.get_tile(x + width, this->y + y).has_shape)
        {
            return;
        }
    }

    ++x;
}

void piece::draw(int field_position, int tile_size, const Color& tile_color, const Color& background) const
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

bool piece::is_colliding(const playfield& field)
{
    if (x < 0)
    {
        return true;
    }

    if (x + width > field.get_width())
    {
        return true;
    }

    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            int index = y * width + x;
            if (!blocks.at(index))
            {
                continue;
            }

            if (field.get_tile(this->x + x, this-> y + y).has_shape)
            {
                return true;
            }
        }
    }

    return false;
}
