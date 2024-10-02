#pragma once

#include "piece.h"
#include "piece_generator.h"
#include "playfield.h"

#include <chrono>
#include <deque>
#include <optional>
#include <vector>

class tetris
{
    public:
        tetris(int width, int height);

        void tick();

        int get_width() const noexcept;
        int get_height() const noexcept;
        
        const tile& get_tile(int x, int y) const;
        const std::optional<piece> get_piece() const;

    private:
        playfield field;
        std::optional<piece> active_piece;
        piece_generator generator;
        std::deque<piece> random_pieces;

        using tetris_clock = std::chrono::steady_clock;
        std::chrono::time_point<tetris_clock> last_falldown_time = tetris_clock::now();
        int level = 1;

        bool should_move_piece_down();
        bool piece_can_move_down();
};
