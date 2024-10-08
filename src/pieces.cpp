#include "pieces.h"

#include <cassert>
#include <map>

static piece::rotation get_next_rotation(piece::rotation current_rotation, piece::rotation twist);

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
            x += 2;
            y -= 1;
        }
        else if (r == rotation::left)
        {
            x += 1;
            y -= 1;
        }
    }
    else if (current_rotation == rotation::right)
    {
        if (r == rotation::right)
        {
            x -= 2;
            y += 2;
        }
        else if (r == rotation::left)
        {
            x -= 2;
            y += 1;
        }
    }
    else if (current_rotation == rotation::twice)
    {
        if (r == rotation::right)
        {
            x += 1;
            y -= 2;
        }
        else if (r == rotation::left)
        {
            x += 2;
            y -= 2;
        }
    }
    else if (current_rotation == rotation::left)
    {
        if (r == rotation::right)
        {
            x -= 1;
            y += 1;
        }
        else if (r == rotation::left)
        {
            x -= 1;
            y += 2;
        }
    }

    current_rotation = get_next_rotation(current_rotation, r);
    set_blocks(current_rotation);
}

static piece::rotation get_next_rotation(piece::rotation current_rotation, piece::rotation twist)
{
    using rotation = piece::rotation;

    assert(twist == rotation::right || twist == rotation::left);

    std::map<std::pair<rotation, rotation>, rotation> rotations
    {
        {{rotation::original, rotation::right}, rotation::right},
        {{rotation::original, rotation::left}, rotation::left},
        {{rotation::right, rotation::right}, rotation::twice},
        {{rotation::right, rotation::left}, rotation::original},
        {{rotation::twice, rotation::right}, rotation::left},
        {{rotation::twice, rotation::left}, rotation::right},
        {{rotation::left, rotation::right}, rotation::original},
        {{rotation::left, rotation::left}, rotation::twice},
    };

    return rotations.at({current_rotation, twist});
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
            x += 1;
        }
        else if (r == rotation::left)
        {
        }
    }
    else if (current_rotation == rotation::right)
    {
        if (r == rotation::right)
        {
            y += 1;
            x -= 1;
        }
        else if (r == rotation::left)
        {
            x -= 1;
        }
    }
    else if (current_rotation == rotation::twice)
    {
        if (r == rotation::right)
        {
            y -= 1;
        }
        else if (r == rotation::left)
        {
            y -= 1;
            x += 1;
        }
    }
    else if (current_rotation == rotation::left)
    {
        if (r == rotation::right)
        {
        }
        else if (r == rotation::left)
        {
            y += 1;
        }
    }

    current_rotation = get_next_rotation(current_rotation, r);
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
            x += 1;
        }
        else if (r == rotation::left)
        {
        }
    }
    else if (current_rotation == rotation::right)
    {
        if (r == rotation::right)
        {
            y += 1;
            x -= 1;
        }
        else if (r == rotation::left)
        {
            x -= 1;
        }
    }
    else if (current_rotation == rotation::twice)
    {
        if (r == rotation::right)
        {
            y -= 1;
        }
        else if (r == rotation::left)
        {
            y -= 1;
            x += 1;
        }
    }
    else if (current_rotation == rotation::left)
    {
        if (r == rotation::right)
        {
        }
        else if (r == rotation::left)
        {
            y += 1;
        }
    }

    current_rotation = get_next_rotation(current_rotation, r);
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
    color = green;
    set_blocks(rotation::original);
}

void s_piece::set_blocks(rotation r)
{
    blocks = std::vector<bool>(width * height, false);

    if (r == rotation::original || r == rotation::twice)
    {
        set_block(1, 0);
        set_block(2, 0);
        set_block(0, 1);
        set_block(1, 1);
    }
    else
    {
        set_block(0, 0);
        set_block(0, 1);
        set_block(1, 1);
        set_block(1, 2);
    } 
}

void s_piece::rotate(rotation r)
{
    assert(r == rotation::right || r == rotation::left);

    std::swap(width, height);

    if (current_rotation == rotation::original)
    {
        if (r == rotation::right)
        {
            x += 1;
        }
        else if (r == rotation::left)
        {
        }
    }
    else if (current_rotation == rotation::right)
    {
        if (r == rotation::right)
        {
            x -= 1;
            y += 1;
        }
        else if (r == rotation::left)
        {
            x -= 1;
        }
    }
    else if (current_rotation == rotation::twice)
    {
        if (r == rotation::right)
        {
            y -= 1;
        }
        else if (r == rotation::left)
        {
            x += 1;
            y -= 1;
        }
    }
    else if (current_rotation == rotation::left)
    {
        if (r == rotation::right)
        {
        }
        else if (r == rotation::left)
        {
            y += 1;
        }
    }

    current_rotation = get_next_rotation(current_rotation, r);
    set_blocks(current_rotation);
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

void z_piece::set_blocks(rotation r)
{
    blocks = std::vector<bool>(width * height, false);

    if (r == rotation::original || r == rotation::twice)
    {
        set_block(0, 0);
        set_block(1, 0);
        set_block(1, 1);
        set_block(2, 1);
    }
    else
    {
        set_block(0, 1);
        set_block(1, 0);
        set_block(1, 1);
        set_block(0, 2);
    } 
}

void z_piece::rotate(rotation r)
{
    assert(r == rotation::right || r == rotation::left);

    std::swap(width, height);

    if (current_rotation == rotation::original)
    {
        if (r == rotation::right)
        {
            x += 1;
        }
        else if (r == rotation::left)
        {
        }
    }
    else if (current_rotation == rotation::right)
    {
        if (r == rotation::right)
        {
            x -= 1;
            y += 1;
        }
        else if (r == rotation::left)
        {
            x -= 1;
        }
    }
    else if (current_rotation == rotation::twice)
    {
        if (r == rotation::right)
        {
            y -= 1;
        }
        else if (r == rotation::left)
        {
            x += 1;
            y -= 1;
        }
    }
    else if (current_rotation == rotation::left)
    {
        if (r == rotation::right)
        {
        }
        else if (r == rotation::left)
        {
            y += 1;
        }
    }

    current_rotation = get_next_rotation(current_rotation, r);
    set_blocks(current_rotation);
}

t_piece::t_piece()
{
    width = 3;
    height = 2;
    x = 3;
    y = 0;
    color = magenta;
    set_blocks(rotation::original);
}

void t_piece::set_blocks(rotation r)
{
    blocks = std::vector<bool>(width * height, false);

    if (r == rotation::original)
    {
        set_block(1, 0);
        set_block(0, 1);
        set_block(1, 1);
        set_block(2, 1);
    }
    else if (r == rotation::right)
    {
        set_block(0, 0);
        set_block(0, 1);
        set_block(1, 1);
        set_block(0, 2);
    } 
    else if (r == rotation::twice)
    {
        set_block(0, 0);
        set_block(1, 0);
        set_block(2, 0);
        set_block(1, 1);
    }
    else
    {
        set_block(1, 0);
        set_block(0, 1);
        set_block(1, 1);
        set_block(1, 2);
    }
}

void t_piece::rotate(rotation r)
{
    assert(r == rotation::right || r == rotation::left);

    std::swap(width, height);

    if (current_rotation == rotation::original)
    {
        if (r == rotation::right)
        {
            x += 1;
        }
        else if (r == rotation::left)
        {
        }
    }
    else if (current_rotation == rotation::right)
    {
        if (r == rotation::right)
        {
            x -= 1;
            y += 1;
        }
        else if (r == rotation::left)
        {
            x -= 1;
        }
    }
    else if (current_rotation == rotation::twice)
    {
        if (r == rotation::right)
        {
            y -= 1;
        }
        else if (r == rotation::left)
        {
            x += 1;
            y -= 1;
        }
    }
    else if (current_rotation == rotation::left)
    {
        if (r == rotation::right)
        {
        }
        else if (r == rotation::left)
        {
            y += 1;
        }
    }

    current_rotation = get_next_rotation(current_rotation, r);
    set_blocks(current_rotation);
}
