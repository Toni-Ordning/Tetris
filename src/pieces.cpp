#include "pieces.h"

#include <cassert>

i_piece::i_piece()
{
    width = 4;
    height = 1;
    x = 3;
    y = 0;
    color = light_blue;
    set_blocks(rotation::original);
}

void i_piece::set_blocks(rotation r)
{
    blocks = std::vector<bool>(width * height, false);

    if (r == rotation::original || r == rotation::twice)
    {
        set_block(0, 0);
        set_block(1, 0);
        set_block(2, 0);
        set_block(3, 0);
    }
    else
    {
        set_block(0, 0);
        set_block(0, 1);
        set_block(0, 2);
        set_block(0, 3);
    } 
}

void i_piece::rotate(rotation r)
{
    assert(r == rotation::right || r == rotation::left);

    std::swap(width, height);

    if (current_rotation == rotation::original)
    {
        if (r == rotation::right)
        {
            current_rotation = rotation::right;
            x += 2;
            y -= 1;
        }
        else if (r == rotation::left)
        {
            current_rotation = rotation::left;
            x += 1;
            y -= 1;
        }
    }
    else if (current_rotation == rotation::right)
    {
        if (r == rotation::right)
        {
            current_rotation = rotation::twice;
            x -= 2;
            y += 2;
        }
        else if (r == rotation::left)
        {
            current_rotation = rotation::original;
            x -= 2;
            y += 1;
        }
    }
    else if (current_rotation == rotation::twice)
    {
        if (r == rotation::right)
        {
            current_rotation = rotation::left;
            x += 1;
            y -= 2;
        }
        else if (r == rotation::left)
        {
            current_rotation = rotation::right;
            x += 2;
            y -= 2;
        }
    }
    else if (current_rotation == rotation::left)
    {
        if (r == rotation::right)
        {
            current_rotation = rotation::original;
            x -= 1;
            y += 1;
        }
        else if (r == rotation::left)
        {
            current_rotation = rotation::twice;
            x -= 1;
            y += 2;
        }
    }

    set_blocks(current_rotation);
}

j_piece::j_piece()
{
    width = 3;
    height = 2;
    x = 3;
    y = 0;
    color = dark_blue;
    set_blocks(rotation::original);
}

void j_piece::set_blocks(rotation r)
{
    blocks = std::vector<bool>(width * height, false);

    if (r == rotation::original)
    {
        set_block(0, 0);
        set_block(0, 1);
        set_block(1, 1);
        set_block(2, 1);
    }
    else if (r == rotation::right)
    {
        set_block(0, 0);
        set_block(1, 0);
        set_block(0, 1);
        set_block(0, 2);
    } 
    else if (r == rotation::twice)
    {
        set_block(0, 0);
        set_block(1, 0);
        set_block(2, 0);
        set_block(2, 1);
    }
    else
    {
        set_block(1, 0);
        set_block(1, 1);
        set_block(0, 2);
        set_block(1, 2);
    }
}

void j_piece::rotate(rotation r)
{
    assert(r == rotation::right || r == rotation::left);
    
    std::swap(width, height);

    if (current_rotation == rotation::original)
    {
        if (r == rotation::right)
        {
            current_rotation = rotation::right;
            x += 1;
        }
        else if (r == rotation::left)
        {
            current_rotation = rotation::left;
        }
    }
    else if (current_rotation == rotation::right)
    {
        if (r == rotation::right)
        {
            current_rotation = rotation::twice;
            y += 1;
            x -= 1;
        }
        else if (r == rotation::left)
        {
            current_rotation = rotation::original;
            x -= 1;
        }
    }
    else if (current_rotation == rotation::twice)
    {
        if (r == rotation::right)
        {
            current_rotation = rotation::left;
            y -= 1;
        }
        else if (r == rotation::left)
        {
            current_rotation = rotation::right;
            y -= 1;
            x += 1;
        }
    }
    else if (current_rotation == rotation::left)
    {
        if (r == rotation::right)
        {
            current_rotation = rotation::original;
        }
        else if (r == rotation::left)
        {
            current_rotation = rotation::twice;
            y += 1;
        }
    }

    set_blocks(current_rotation);
}

l_piece::l_piece()
{
    width = 3;
    height = 2;
    x = 3;
    y = 0;
    color = orange;
    set_blocks(rotation::original);
}

void l_piece::set_blocks(rotation r)
{
    blocks = std::vector<bool>(width * height, false);

    if (r == rotation::original)
    {
        set_block(2, 0);
        set_block(0, 1);
        set_block(1, 1);
        set_block(2, 1);
    }
    else if (r == rotation::right)
    {
        set_block(0, 0);
        set_block(0, 1);
        set_block(0, 2);
        set_block(1, 2);
    } 
    else if (r == rotation::twice)
    {
        set_block(0, 0);
        set_block(1, 0);
        set_block(2, 0);
        set_block(0, 1);
    }
    else
    {
        set_block(0, 0);
        set_block(1, 0);
        set_block(1, 1);
        set_block(1, 2);
    }
}

void l_piece::rotate(rotation r)
{
    assert(r == rotation::right || r == rotation::left);

    std::swap(width, height);

    if (current_rotation == rotation::original)
    {
        if (r == rotation::right)
        {
            current_rotation = rotation::right;
            x += 1;
        }
        else if (r == rotation::left)
        {
            current_rotation = rotation::left;
        }
    }
    else if (current_rotation == rotation::right)
    {
        if (r == rotation::right)
        {
            current_rotation = rotation::twice;
            y += 1;
            x -= 1;
        }
        else if (r == rotation::left)
        {
            current_rotation = rotation::original;
            x -= 1;
        }
    }
    else if (current_rotation == rotation::twice)
    {
        if (r == rotation::right)
        {
            current_rotation = rotation::left;
            y -= 1;
        }
        else if (r == rotation::left)
        {
            current_rotation = rotation::right;
            y -= 1;
            x += 1;
        }
    }
    else if (current_rotation == rotation::left)
    {
        if (r == rotation::right)
        {
            current_rotation = rotation::original;
        }
        else if (r == rotation::left)
        {
            current_rotation = rotation::twice;
            y += 1;
        }
    }

    set_blocks(current_rotation);
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

// No need to rotate o_piece
void o_piece::rotate(rotation r)
{
}

s_piece::s_piece()
{
    width = 3;
    height = 2;
    x = 3;
    y = 0;
    blocks = std::vector<bool>(width * height, false);
    set_block(1, 0);
    set_block(2, 0);
    set_block(0, 1);
    set_block(1, 1);
    color = green;
}

void s_piece::rotate(rotation r)
{
    assert(r == rotation::right || r == rotation::left);

    if (current_rotation == rotation::original)
    {
        if (r == rotation::right)
        {
            current_rotation = rotation::right;
            std::swap(width, height);
            x += 1;
            blocks = std::vector<bool>(width * height, false);
            set_block(0, 0);
            set_block(0, 1);
            set_block(1, 1);
            set_block(1, 2);
        }
        else if (r == rotation::left)
        {
            current_rotation = rotation::left;
            std::swap(width, height);
            blocks = std::vector<bool>(width * height, false);
            set_block(0, 0);
            set_block(0, 1);
            set_block(1, 1);
            set_block(1, 2);
        }
    }
    else if (current_rotation == rotation::right)
    {
        if (r == rotation::right)
        {
            current_rotation = rotation::twice;
            std::swap(width, height);
            x -= 1;
            y += 1;
            blocks = std::vector<bool>(width * height, false);
            set_block(1, 0);
            set_block(2, 0);
            set_block(0, 1);
            set_block(1, 1);
        }
        else if (r == rotation::left)
        {
            current_rotation = rotation::original;
            std::swap(width, height);
            x -= 1;
            blocks = std::vector<bool>(width * height, false);
            set_block(1, 0);
            set_block(2, 0);
            set_block(0, 1);
            set_block(1, 1);
        }
    }
    else if (current_rotation == rotation::twice)
    {
        if (r == rotation::right)
        {
            current_rotation = rotation::left;
            std::swap(width, height);
            y -= 1;
            blocks = std::vector<bool>(width * height, false);
            set_block(0, 0);
            set_block(0, 1);
            set_block(1, 1);
            set_block(1, 2);
        }
        else if (r == rotation::left)
        {
            current_rotation = rotation::right;
            std::swap(width, height);
            x += 1;
            y -= 1;
            blocks = std::vector<bool>(width * height, false);
            set_block(0, 0);
            set_block(0, 1);
            set_block(1, 1);
            set_block(1, 2);
        }
    }
    else if (current_rotation == rotation::left)
    {
        if (r == rotation::right)
        {
            current_rotation = rotation::original;
            std::swap(width, height);
            blocks = std::vector<bool>(width * height, false);
            set_block(1, 0);
            set_block(2, 0);
            set_block(0, 1);
            set_block(1, 1);
        }
        else if (r == rotation::left)
        {
            current_rotation = rotation::twice;
            std::swap(width, height);
            y += 1;
            blocks = std::vector<bool>(width * height, false);
            set_block(1, 0);
            set_block(2, 0);
            set_block(0, 1);
            set_block(1, 1);
        }
    }
}

z_piece::z_piece()
{
    width = 3;
    height = 2;
    x = 3;
    y = 0;
    blocks = std::vector<bool>(width * height, false);
    set_block(0, 0);
    set_block(1, 0);
    set_block(1, 1);
    set_block(2, 1);
    color = red;
}

void z_piece::rotate(rotation r)
{
    assert(r == rotation::right || r == rotation::left);

    if (current_rotation == rotation::original)
    {
        if (r == rotation::right)
        {
            current_rotation = rotation::right;
            std::swap(width, height);
            x += 1;
            blocks = std::vector<bool>(width * height, false);
            set_block(0, 1);
            set_block(1, 0);
            set_block(1, 1);
            set_block(0, 2);
        }
        else if (r == rotation::left)
        {
            current_rotation = rotation::left;
            std::swap(width, height);
            blocks = std::vector<bool>(width * height, false);
            set_block(0, 1);
            set_block(1, 0);
            set_block(1, 1);
            set_block(0, 2);
        }
    }
    else if (current_rotation == rotation::right)
    {
        if (r == rotation::right)
        {
            current_rotation = rotation::twice;
            std::swap(width, height);
            x -= 1;
            y += 1;
            blocks = std::vector<bool>(width * height, false);
            set_block(0, 0);
            set_block(1, 0);
            set_block(1, 1);
            set_block(2, 1);
        }
        else if (r == rotation::left)
        {
            current_rotation = rotation::original;
            std::swap(width, height);
            x -= 1;
            blocks = std::vector<bool>(width * height, false);
            set_block(0, 0);
            set_block(1, 0);
            set_block(1, 1);
            set_block(2, 1);
        }
    }
    else if (current_rotation == rotation::twice)
    {
        if (r == rotation::right)
        {
            current_rotation = rotation::left;
            std::swap(width, height);
            y -= 1;
            blocks = std::vector<bool>(width * height, false);
            set_block(0, 1);
            set_block(1, 0);
            set_block(1, 1);
            set_block(0, 2);
        }
        else if (r == rotation::left)
        {
            current_rotation = rotation::right;
            std::swap(width, height);
            x += 1;
            y -= 1;
            blocks = std::vector<bool>(width * height, false);
            set_block(0, 1);
            set_block(1, 0);
            set_block(1, 1);
            set_block(0, 2);
        }
    }
    else if (current_rotation == rotation::left)
    {
        if (r == rotation::right)
        {
            current_rotation = rotation::original;
            std::swap(width, height);
            blocks = std::vector<bool>(width * height, false);
            set_block(0, 0);
            set_block(1, 0);
            set_block(1, 1);
            set_block(2, 1);
        }
        else if (r == rotation::left)
        {
            current_rotation = rotation::twice;
            std::swap(width, height);
            y += 1;
            blocks = std::vector<bool>(width * height, false);
            set_block(0, 0);
            set_block(1, 0);
            set_block(1, 1);
            set_block(2, 1);
        }
    }
}

t_piece::t_piece()
{
    width = 3;
    height = 2;
    x = 3;
    y = 0;
    blocks = std::vector<bool>(width * height, false);
    set_block(1, 0);
    set_block(0, 1);
    set_block(1, 1);
    set_block(2, 1);
    color = magenta;
}


void t_piece::rotate(rotation r)
{
    assert(r == rotation::right || r == rotation::left);

    if (current_rotation == rotation::original)
    {
        if (r == rotation::right)
        {
            current_rotation = rotation::right;
            std::swap(width, height);
            x += 1;
            blocks = std::vector<bool>(width * height, false);
            set_block(0, 0);
            set_block(0, 1);
            set_block(1, 1);
            set_block(0, 2);
        }
        else if (r == rotation::left)
        {
            current_rotation = rotation::left;
            std::swap(width, height);
            blocks = std::vector<bool>(width * height, false);
            set_block(1, 0);
            set_block(0, 1);
            set_block(1, 1);
            set_block(1, 2);
        }
    }
    else if (current_rotation == rotation::right)
    {
        if (r == rotation::right)
        {
            current_rotation = rotation::twice;
            std::swap(width, height);
            x -= 1;
            y += 1;
            blocks = std::vector<bool>(width * height, false);
            set_block(0, 0);
            set_block(1, 0);
            set_block(2, 0);
            set_block(1, 1);
        }
        else if (r == rotation::left)
        {
            current_rotation = rotation::original;
            std::swap(width, height);
            x -= 1;
            blocks = std::vector<bool>(width * height, false);
            set_block(1, 0);
            set_block(0, 1);
            set_block(1, 1);
            set_block(2, 1);
        }
    }
    else if (current_rotation == rotation::twice)
    {
        if (r == rotation::right)
        {
            current_rotation = rotation::left;
            std::swap(width, height);
            y -= 1;
            blocks = std::vector<bool>(width * height, false);
            set_block(1, 0);
            set_block(0, 1);
            set_block(1, 1);
            set_block(1, 2);
        }
        else if (r == rotation::left)
        {
            current_rotation = rotation::right;
            std::swap(width, height);
            x += 1;
            y -= 1;
            blocks = std::vector<bool>(width * height, false);
            set_block(0, 0);
            set_block(0, 1);
            set_block(1, 1);
            set_block(0, 2);
        }
    }
    else if (current_rotation == rotation::left)
    {
        if (r == rotation::right)
        {
            current_rotation = rotation::original;
            std::swap(width, height);
            blocks = std::vector<bool>(width * height, false);
            set_block(1, 0);
            set_block(0, 1);
            set_block(1, 1);
            set_block(2, 1);
        }
        else if (r == rotation::left)
        {
            current_rotation = rotation::twice;
            std::swap(width, height);
            y += 1;
            blocks = std::vector<bool>(width * height, false);
            set_block(0, 0);
            set_block(1, 0);
            set_block(2, 0);
            set_block(1, 1);
        }
    }
}
