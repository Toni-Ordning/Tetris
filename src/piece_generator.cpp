#include "piece_generator.h"

#include <algorithm>
#include <iostream>
#include <random>

std::deque<std::unique_ptr<piece>> piece_generator::generate_pieces(const playfield& field)
{
    std::deque<std::unique_ptr<piece>> pieces;

    pieces.emplace_back(build_piece(piece::piece_type::i, field));
    pieces.emplace_back(build_piece(piece::piece_type::j, field));
    pieces.emplace_back(build_piece(piece::piece_type::l, field));
    pieces.emplace_back(build_piece(piece::piece_type::o, field));
    pieces.emplace_back(build_piece(piece::piece_type::s, field));
    pieces.emplace_back(build_piece(piece::piece_type::z, field));
    pieces.emplace_back(build_piece(piece::piece_type::t, field));
    std::random_device rd;
    std::mt19937 rng(rd());
    std::ranges::shuffle(pieces, rng);

    return pieces;
}
