#pragma once

#include "piece.h"

#include <deque>

class piece_generator
{
    public:
        std::deque<piece> generate_pieces();
};
