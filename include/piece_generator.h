#pragma once

#include "piece.h"
#include "playfield.h"

#include <deque>

class piece_generator
{
    public:
        std::deque<std::unique_ptr<piece>> generate_pieces(const playfield& field);
};
