#pragma once

#include <raylib.h>

#include <vector>

#include "playfield.h"

class piece
{
    public:
        enum class piece_type
        {
            i,
            j,
            l,
            o,
            s,
            z,
            t
        };

        piece(piece_type type);

        int get_x() const noexcept;
        int get_y() const noexcept;
        int get_width() const noexcept;
        int get_height() const noexcept;

        void move_down();
        void move_left(const playfield& field);
        void move_right(const playfield& field);

        bool get_block(int x, int y) const;
        Color get_color() const;

        void draw(int field_position, int tile_size, const Color& tile_color, const Color& background);

    private:
        int width = 0;
        int height = 0;
        int x = 0;
        int y = 0;
        std::vector<bool> blocks;
        
        void build_piece(piece_type type);
        void set_block(int x, int y);
};
