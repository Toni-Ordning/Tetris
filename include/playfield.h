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

    private:
        int width = 0;
        int height = 0;
        std::vector<tile> tiles;
};
