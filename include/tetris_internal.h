#pragma once

#include <chrono>

namespace internal
{
    /** Returns the interval of game update time in seconds **/
    float get_interval(int level) noexcept;
}
