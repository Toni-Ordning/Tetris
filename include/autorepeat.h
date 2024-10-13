#pragma once

#include "input.h"
#include "tetris_clock.h"

#include <chrono>
#include <map>

// DAS (Delayed Auto Shift) a.k.a. autorepeat system. https://tetris.wiki/DAS
// Autorepeat does not start until set amount of time (delay) has passed.
// Autorepeat occurs every n game ticks.

class autorepeat
{
    public:
        void start_processing();
        bool should_autorepeat(input_event e);
        void set_delay(int tickrate);
        void set_tickrate(int tickrate);

    private:
        struct event_details
        {
            int delay_ticks;
            int rate_ticks;
        };

        std::map<input_event, event_details> current_events;
        std::map<input_event, event_details> previous_events;
        int delay = 12;
        int rate = 2;
};
