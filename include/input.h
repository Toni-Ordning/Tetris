#pragma once

#include <deque>

enum class input_event
{
    hard_drop,
    move_piece_left,
    move_piece_right,
    soft_drop,
    rotate_clockwise,
    rotate_counterclockwise
};

std::deque<input_event> get_input_events();
