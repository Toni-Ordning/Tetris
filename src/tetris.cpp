#include "tetris.h"

#include "tetris_internal.h"

#include <algorithm>
#include <iostream>
#include <stdexcept>

tetris::tetris(int width, int height)
    : field(width, height)
{
    std::time_t now = time(nullptr);
    if (now == (std::time_t)(-1))
    {
        throw std::runtime_error{"Failed to get current time"};
    }
}

void tetris::tick()
{
    if (!active_piece)
    {
        if (random_pieces.empty())
        {
            random_pieces = generator.generate_pieces(field);
        }

        active_piece = std::move(random_pieces.front());
        random_pieces.pop_front();

        if (!active_piece->can_move_down())
        {
            state = game_state::over;
        }
    }

    if (!active_piece->can_move_down())
    {
        for (int y = active_piece->get_height() - 1; y >= 0; --y)
        {
            for (int x = 0; x < active_piece->get_width(); ++x)
            {
                if (active_piece->get_block(x, y))
                {
                    field.set_tile(active_piece->get_x() + x, active_piece->get_y() + y, active_piece->get_color());
                }
            }
        }

        active_piece.reset();

        clear_complete_lines();
    }
    else if (should_move_piece_down())
    {
        active_piece->move_down();
    }

    guide_piece = nullptr;
    if (active_piece)
    {
        guide_piece = active_piece->copy();
        while (guide_piece->can_move_down())
        {
            guide_piece->move_down();
        }
    }

    update_level();
}

int tetris::get_width() const noexcept
{
    return field.get_width();
}

int tetris::get_height() const noexcept
{
    return field.get_height();
}

int tetris::get_score() const noexcept
{
    return score;
}

int tetris::get_level() const noexcept
{
    return level;
}

const tile& tetris::get_tile(int x, int y) const
{
    return field.get_tile(x, y);
}

const std::deque<std::unique_ptr<piece>>& tetris::get_pieces() const noexcept
{
    return random_pieces;
}

bool tetris::should_move_piece_down()
{
    using seconds = std::chrono::seconds;

    const float interval = internal::get_interval(level);
    const tetris_time_point now = tetris_clock::now();
    if (now - last_falldown_time > interval * seconds(1))
    {
        last_falldown_time = now;
        return true;
    }

    return false;
}

void tetris::process_events(std::deque<input_event>& events)
{
    if (!active_piece)
    {
        return;
    }

    repeat.start_processing();

    for (input_event event : events)
    {
        switch (event)
        {
            case input_event::hard_drop:
                if (!repeat.should_autorepeat(event))
                {
                    continue;
                }

                while (active_piece->can_move_down())
                {
                    active_piece->move_down();
                }
                break;
            case input_event::move_piece_left:
                if (repeat.should_autorepeat(event))
                {
                    active_piece->move_left();
                }
                break;
            case input_event::move_piece_right:
                if (repeat.should_autorepeat(event))
                {
                    active_piece->move_right();
                }
                break;
            case input_event::soft_drop:
                if (repeat.should_autorepeat(event) && active_piece->can_move_down())
                {
                    active_piece->move_down();
                }
                break;
            case input_event::rotate_clockwise:
                if (repeat.should_autorepeat(event))
                {
                    if (!active_piece->can_rotate(piece::rotation::right))
                    {
                        return;
                    }

                    active_piece->rotate(piece::rotation::right);
                }
                break;
            case input_event::rotate_counterclockwise:
                if (repeat.should_autorepeat(event))
                {
                    if (!active_piece->can_rotate(piece::rotation::left))
                    {
                        return;
                    }

                    active_piece->rotate(piece::rotation::left);
                }
                break;
        }
    }
}

void tetris::clear_complete_lines()
{
    for (int y = 0; y < field.get_height(); ++y)
    {
        bool should_remove_line = true;
        for (int x = 0; x < field.get_width(); ++x)
        {
            if (!field.get_tile(x, y).has_shape)
            {
                should_remove_line = false;
            }
        }

        if (!should_remove_line)
        {
            continue;
        }

        field.clear_line(y);
        ++score;
    }
}

piece* tetris::get_piece() const
{
    return active_piece.get();
}

piece* tetris::get_guide_piece() const
{
    return guide_piece.get();
}

void tetris::update_level()
{
    int new_level = 1;
    int current_score = score;
    while (current_score > 10)
    {
        ++new_level;
        current_score -= 10;
    }

    level = new_level;
}
