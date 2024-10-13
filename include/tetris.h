#pragma once

#include "autorepeat.h"
#include "input.h"
#include "piece.h"
#include "piece_generator.h"
#include "playfield.h"
#include "tetris_clock.h"

#include <chrono>
#include <deque>
#include <optional>
#include <vector>

enum class game_state
{
    over,
    running,
};

class tetris
{
    public:
        tetris(int width, int height);

        void tick();
        void process_events(std::deque<input_event>& events);

        int get_width() const noexcept;
        int get_height() const noexcept;

        const tile& get_tile(int x, int y) const;
        piece* get_piece() const;

        game_state state = game_state::running;

    private:
        autorepeat repeat;
        playfield field;
        std::unique_ptr<piece> active_piece = nullptr;
        piece_generator generator;
        std::deque<std::unique_ptr<piece>> random_pieces;

        tetris_time_point last_falldown_time = tetris_clock::now();
        int level = 1;

        bool should_move_piece_down();
        void clear_complete_lines();
};
