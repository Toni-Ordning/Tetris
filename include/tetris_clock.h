#pragma once

#include <chrono>

using tetris_clock = std::chrono::steady_clock;
using tetris_time_point = std::chrono::time_point<tetris_clock>;
