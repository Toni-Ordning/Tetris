#include "pieces.h"

#include <cassert>
#include <map>

static piece::rotation get_next_rotation(piece::rotation current_rotation, piece::rotation twist);
static void set_rotation_offset(piece::rotation old, piece::rotation current, bool is_i_piece, int& x, int& y);

using rotation_pair = std::pair<piece::rotation, piece::rotation>;
using offset = std::pair<int, int>;

const std::map<rotation_pair, offset> i_piece_offsets
{
    {{piece::rotation::original, piece::rotation::right}, {2, -1}},
    {{piece::rotation::original, piece::rotation::left}, {1, -1}},
    {{piece::rotation::right, piece::rotation::right}, {-2, 2}},
    {{piece::rotation::right, piece::rotation::left}, {-2, 1}},
    {{piece::rotation::twice, piece::rotation::right}, {1, -2}},
    {{piece::rotation::twice, piece::rotation::left}, {2, -2}},
    {{piece::rotation::left, piece::rotation::right}, {-1, 1}},
    {{piece::rotation::left, piece::rotation::left}, {-1, 2}},
};

const std::map<rotation_pair, offset> other_piece_offsets
{
    {{piece::rotation::original, piece::rotation::right}, {1, 0}},
    {{piece::rotation::right, piece::rotation::right}, {-1, 1}},
    {{piece::rotation::right, piece::rotation::left}, {-1, 0}},
    {{piece::rotation::twice, piece::rotation::right}, {0, -1}},
    {{piece::rotation::twice, piece::rotation::left}, {1, -1}},
    {{piece::rotation::left, piece::rotation::left}, {0, 1}},
};

i_piece::i_piece(const playfield& field)
    : piece(field)
{
    width = 4;
    height = 1;
    x = 3;
    y = 0;
    color = light_blue;
    set_blocks(rotation::original);
    type = piece_type::i;
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

bool i_piece::can_rotate(rotation r)
{
    assert(r == rotation::right || r == rotation::left);

    i_piece copy = *this;
    copy.rotate(r);

    return !copy.is_colliding();
}

void i_piece::rotate(rotation r)
{
    assert(r == rotation::right || r == rotation::left);

    std::swap(width, height);
    set_rotation_offset(current_rotation, r, true, x, y);
    current_rotation = get_next_rotation(current_rotation, r);
    set_blocks(current_rotation);
}

static void set_rotation_offset(piece::rotation old, piece::rotation current, bool is_i_piece, int& x, int& y)
{
    const std::map<rotation_pair, offset>& offsets = is_i_piece
        ? i_piece_offsets
        : other_piece_offsets;

    if (offsets.contains({old, current}))
    {
        offset off = offsets.at({old, current});
        x += off.first;
        y += off.second;
    }
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

j_piece::j_piece(const playfield& field)
    : piece(field)
{
    width = 3;
    height = 2;
    x = 3;
    y = 0;
    color = dark_blue;
    set_blocks(rotation::original);
    type = piece_type::j;
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

bool j_piece::can_rotate(rotation r)
{
    assert(r == rotation::right || r == rotation::left);

    j_piece copy = *this;
    copy.rotate(r);

    return !copy.is_colliding();
}

void j_piece::rotate(rotation r)
{
    assert(r == rotation::right || r == rotation::left);
    
    std::swap(width, height);
    set_rotation_offset(current_rotation, r, false, x, y);
    current_rotation = get_next_rotation(current_rotation, r);
    set_blocks(current_rotation);
}

l_piece::l_piece(const playfield& field)
    : piece(field)
{
    width = 3;
    height = 2;
    x = 3;
    y = 0;
    color = orange;
    set_blocks(rotation::original);
    type = piece_type::l;
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

bool l_piece::can_rotate(rotation r)
{
    assert(r == rotation::right || r == rotation::left);

    l_piece copy = *this;
    copy.rotate(r);

    return !copy.is_colliding();
}

void l_piece::rotate(rotation r)
{
    assert(r == rotation::right || r == rotation::left);

    std::swap(width, height);
    set_rotation_offset(current_rotation, r, false, x, y);
    current_rotation = get_next_rotation(current_rotation, r);
    set_blocks(current_rotation);
}

o_piece::o_piece(const playfield& field)
    : piece(field)
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
    type = piece_type::o;
}

// No need to rotate o_piece
bool o_piece::can_rotate(rotation r)
{
    return true;
}

void o_piece::rotate(rotation r)
{
}

s_piece::s_piece(const playfield& field)
    : piece(field)
{
    width = 3;
    height = 2;
    x = 3;
    y = 0;
    color = green;
    set_blocks(rotation::original);
    type = piece_type::s;
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

bool s_piece::can_rotate(rotation r)
{
    assert(r == rotation::right || r == rotation::left);

    s_piece copy = *this;
    copy.rotate(r);

    return !copy.is_colliding();
}

void s_piece::rotate(rotation r)
{
    assert(r == rotation::right || r == rotation::left);

    std::swap(width, height);
    set_rotation_offset(current_rotation, r, false, x, y);
    current_rotation = get_next_rotation(current_rotation, r);
    set_blocks(current_rotation);
}

z_piece::z_piece(const playfield& field)
    : piece(field)
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
    type = piece_type::z;
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

bool z_piece::can_rotate(rotation r)
{
    assert(r == rotation::right || r == rotation::left);

    z_piece copy = *this;
    copy.rotate(r);

    return !copy.is_colliding();
}

void z_piece::rotate(rotation r)
{
    assert(r == rotation::right || r == rotation::left);

    std::swap(width, height);
    set_rotation_offset(current_rotation, r, false, x, y);
    current_rotation = get_next_rotation(current_rotation, r);
    set_blocks(current_rotation);
}

t_piece::t_piece(const playfield& field)
    : piece(field)
{
    width = 3;
    height = 2;
    x = 3;
    y = 0;
    color = magenta;
    set_blocks(rotation::original);
    type = piece_type::t;
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

bool t_piece::can_rotate(rotation r)
{
    assert(r == rotation::right || r == rotation::left);

    t_piece copy = *this;
    copy.rotate(r);

    return !copy.is_colliding();
}

void t_piece::rotate(rotation r)
{
    assert(r == rotation::right || r == rotation::left);

    std::swap(width, height);
    set_rotation_offset(current_rotation, r, false, x, y);
    current_rotation = get_next_rotation(current_rotation, r);
    set_blocks(current_rotation);
}
