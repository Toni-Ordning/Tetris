#include "input.h"

#include "raylib.h"

std::deque<input_event> get_input_events()
{
    std::deque<input_event> events;

    // Only allow moving piece left or right, not both
    if (IsKeyDown(KEY_LEFT) && !IsKeyDown(KEY_RIGHT))
    {
        events.push_back(input_event::move_piece_left);
    }
    
    if (IsKeyDown(KEY_RIGHT) && !IsKeyDown(KEY_LEFT))
    {
        events.push_back(input_event::move_piece_right);
    }

    if (IsKeyDown(KEY_DOWN))
    {
        events.push_back(input_event::soft_drop);
    }

    if (IsKeyDown(KEY_UP))
    {
        events.push_back(input_event::rotate_clockwise);
    }

    if (IsKeyDown(KEY_SPACE))
    {
        events.push_back(input_event::hard_drop);
    }

    if (IsKeyDown(KEY_Z) || IsKeyDown(KEY_LEFT_CONTROL))
    {
        events.push_back(input_event::rotate_counterclockwise);
    }

    return events;
}
