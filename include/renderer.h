#pragma once

#include "tetris.h"

class renderer
{
    public:
        renderer(const tetris& game);

        void draw();

    private:
        const tetris& game;

        void draw_bag();
};
