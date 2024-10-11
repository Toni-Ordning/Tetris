#pragma once

#include "raylib.h"

#include "tile.h"

#include <vector>

class playfield
{
    public:
        playfield(int width, int height);

        int get_width() const noexcept;
        int get_height() const noexcept;

        const tile& get_tile(int x, int y) const;
        void set_tile(int x, int y, const Color& color);

        void clear_line(int y);
        void move_lines_down(int y);

    private:
        int width = 0;
        int height = 0;
        std::vector<tile> tiles;

        int get_index(int x, int y) const;
};
