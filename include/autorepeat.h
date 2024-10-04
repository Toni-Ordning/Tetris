#pragma once

#include "input.h"

#include <chrono>

// DAS (Delayed Auto Shift) a.k.a. autorepeat system. https://tetris.wiki/DAS
// Autorepeat does not start until set amount of time (delay) has passed.
// Autorepeat occurs every n game ticks.

bool should_autorepeat(input_event e);

void reset_autorepeat();
