#include "pieces.h"

#include <cassert>

i_piece::i_piece()
{
    width = 4;
    height = 1;
    blocks = std::vector<bool>(width * height, false);
    x = 3;
    y = 0;
    set_block(0, 0);
    set_block(1, 0);
    set_block(2, 0);
    set_block(3, 0);
    color = light_blue;
}

void i_piece::rotate(rotation r)
{
    if (current_rotation == rotation::original)
    {
        if (r == rotation::right)
        {
            current_rotation = rotation::right;
            height = width;
            width = 1;
            x += 2;
            y -= 1;
        }
        else if (r == rotation::left)
        {
            current_rotation = rotation::left;
            height = width;
            width = 1;
            x += 1;
            y -= 1;
        }
    }
    else if (current_rotation == rotation::right)
    {
        if (r == rotation::right)
        {
            current_rotation = rotation::twice;
            width = height;
            height = 1;
            x -= 2;
            y += 2;
        }
        else if (r == rotation::left)
        {
            current_rotation = rotation::original;
            width = height;
            height = 1;
            x -= 2;
            y += 1;
        }
    }
    else if (current_rotation == rotation::twice)
    {
        if (r == rotation::right)
        {
            current_rotation = rotation::left;
            height = width;
            width = 1;
            x += 1;
            y -= 2;
        }
        else if (r == rotation::left)
        {
            current_rotation = rotation::right;
            height = width;
            width = 1;
            x += 2;
            y -= 2;
        }
    }
    else if (current_rotation == rotation::left)
    {
        if (r == rotation::right)
        {
            current_rotation = rotation::original;
            width = height;
            height = 1;
            x -= 1;
            y += 1;
        }
        else if (r == rotation::left)
        {
            current_rotation = rotation::twice;
            width = height;
            height = 1;
            x -= 1;
            y += 2;
        }
    }
    else
    {
        assert(false);
    }
}

j_piece::j_piece()
{
    width = 3;
    height = 2;
    blocks = std::vector<bool>(width * height, false);
    x = 3;
    y = 0;
    set_block(0, 0);
    set_block(0, 1);
    set_block(1, 1);
    set_block(2, 1);
    color = dark_blue;
}

void j_piece::rotate(rotation r)
{

}

l_piece::l_piece()
{
    width = 3;
    height = 2;
    blocks = std::vector<bool>(width * height, false);
    x = 3;
    y = 0;
    set_block(2, 0);
    set_block(0, 1);
    set_block(1, 1);
    set_block(2, 1);
    color = orange;
}

void l_piece::rotate(rotation r)
{

}

o_piece::o_piece()
{
    width = 2;
    height = 2;
    blocks = std::vector<bool>(width * height, false);
    x = 4;
    y = 0;
    set_block(0, 0);
    set_block(0, 1);
    set_block(1, 0);
    set_block(1, 1);
    color = yellow;
}

void o_piece::rotate(rotation r)
{

}

s_piece::s_piece()
{
    width = 3;
    height = 2;
    blocks = std::vector<bool>(width * height, false);
    x = 3;
    y = 0;
    set_block(1, 0);
    set_block(2, 0);
    set_block(0, 1);
    set_block(1, 1);
    color = green;
}

void s_piece::rotate(rotation r)
{

}

z_piece::z_piece()
{
    width = 3;
    height = 2;
    blocks = std::vector<bool>(width * height, false);
    x = 3;
    y = 0;
    set_block(0, 0);
    set_block(1, 0);
    set_block(1, 1);
    set_block(2, 1);
    color = red;
}

void z_piece::rotate(rotation r)
{

}

t_piece::t_piece()
{
    width = 3;
    height = 2;
    blocks = std::vector<bool>(width * height, false);
    x = 3;
    y = 0;
    set_block(1, 0);
    set_block(0, 1);
    set_block(1, 1);
    set_block(2, 1);
    color = magenta;
}


void t_piece::rotate(rotation r)
{

}
