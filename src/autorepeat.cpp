#include "autorepeat.h"

void autorepeat::start_processing()
{
    for (auto iter = previous_events.begin(); iter != previous_events.end();)
    {
        if (!current_events.contains(iter->first))
        {
            iter = previous_events.erase(iter);
        }
        else
        {
            ++iter;
        }
    }

    previous_events = current_events;
    current_events.clear();
}

bool autorepeat::should_autorepeat(input_event e)
{
    if (!previous_events.contains(e))
    {
        current_events[e] = event_details{0, 0};
        return true;
    }

    int& delay_ticks = previous_events.at(e).delay_ticks;
    int& rate_ticks = previous_events.at(e).rate_ticks;

    ++delay_ticks;
    ++rate_ticks;

    if (delay_ticks < delay)
    {
        current_events[e] = previous_events.at(e);
        return false;
    }

    if (rate_ticks < rate)
    {
        current_events[e] = previous_events.at(e);
        return false;
    }

    rate_ticks = 0;
    current_events[e] = previous_events.at(e);
    return true;
}

void autorepeat::set_delay(int tickrate)
{
    delay = tickrate;
}

void autorepeat::set_tickrate(int tickrate)
{
    rate = tickrate;
}
