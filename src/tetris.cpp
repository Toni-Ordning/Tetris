#include "tetris.h"

#include "tetris_internal.h"

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
            std::cout << "Generating pieces" << std::endl;
            random_pieces = generator.generate_pieces();
        }

        active_piece = random_pieces.front();
        random_pieces.pop_front();
    }

    if (!piece_can_move_down())
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
    }
    else if (should_move_piece_down())
    {
        active_piece->move_down();
    }
}

int tetris::get_width() const noexcept
{
    return field.get_width();
}

int tetris::get_height() const noexcept
{
    return field.get_height();
}

const tile& tetris::get_tile(int x, int y) const
{
    return field.get_tile(x, y);
}

const std::optional<piece> tetris::get_piece() const
{
    return active_piece;
}

bool tetris::should_move_piece_down()
{
    using time_point = std::chrono::time_point<tetris_clock>;
    using seconds = std::chrono::seconds;

    const float interval = internal::get_interval(level);
    const time_point now = tetris_clock::now();
    if (now - last_falldown_time > interval * seconds(1))
    {
        last_falldown_time = now;
        return true;
    }
    
    return false;
}

bool tetris::piece_can_move_down()
{
    for (int y = active_piece->get_height() - 1; y >= 0; --y)
    {
        for (int x = 0; x < active_piece->get_width(); ++x)
        {
            if (!active_piece->get_block(x, y))
            {
                continue;
            }

            if (active_piece->get_y() + y + 1 >= field.get_height())
            {
                return false;
            }

            if (field.get_tile(active_piece->get_x() + x, active_piece->get_y() + y + 1).has_shape)
            {
                return false;
            }
        }
    }
    
    return true;
}
