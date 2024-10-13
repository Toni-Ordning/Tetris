#pragma once

#include <raylib.h>

#include <memory>
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
            t,
        };

        enum class rotation
        {
            original,
            right,
            left,
            twice,
        };

        piece(const playfield& field);
        virtual ~piece() = default;

        virtual bool can_rotate(rotation r) = 0;
        virtual void rotate(rotation r) = 0;

        int get_x() const noexcept;
        int get_y() const noexcept;
        int get_width() const noexcept;
        int get_height() const noexcept;
        piece_type get_type() const noexcept;

        bool can_move_down();
        void move_down();
        void move_left();
        void move_right();

        bool get_block(int x, int y) const;
        Color get_color() const;

        void draw(int field_position, int tile_size, const Color& tile_color, const Color& background) const;

        std::unique_ptr<piece> copy();
        
    protected: 
        int width = 0;
        int height = 0;
        int x = 0;
        int y = 0;
        std::vector<bool> blocks;
        Color color = light_white;
        rotation current_rotation = rotation::original;
        piece_type type;

        const playfield& field;
        
        void set_block(int x, int y);
        bool is_colliding();
};

std::unique_ptr<piece> build_piece(piece::piece_type type, const playfield& field);
