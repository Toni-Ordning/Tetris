#include "autorepeat.h"

#include "tetris_clock.h"

#include <optional>

constexpr std::chrono::duration delay = std::chrono::milliseconds(300);
constexpr int rate = 2;
std::optional<input_event> last_event;
tetris_time_point event_changed_time;
int autorepeat_ticks = 0;

bool should_autorepeat(input_event e)
{
    if (!last_event || *last_event != e)
    {
        last_event = e;
        event_changed_time = tetris_clock::now();
        autorepeat_ticks = 0;
        return true;
    }

    if (tetris_clock::now() - event_changed_time < delay)
    {
        autorepeat_ticks = 0;
        return false;
    }

    if (++autorepeat_ticks < rate)
    {
        return false;
    }

    autorepeat_ticks = 0;
    return true;
}

void reset_autorepeat()
{
    last_event.reset();
}
