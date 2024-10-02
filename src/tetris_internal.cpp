#include "tetris_internal.h"

#include <cmath>

float internal::get_interval(int level) noexcept
{
    float time = pow(0.8 - ((level-1) * 0.007), level-1);
    return time;
}
