#include "piece_generator.h"

#include <algorithm>
#include <iostream>
#include <random>

std::deque<piece> piece_generator::generate_pieces()
{
    std::deque<piece> pieces;

    pieces.emplace_back(piece(piece::piece_type::i));
    pieces.emplace_back(piece(piece::piece_type::j));
    pieces.emplace_back(piece(piece::piece_type::l));
    pieces.emplace_back(piece(piece::piece_type::o));
    pieces.emplace_back(piece(piece::piece_type::s));
    pieces.emplace_back(piece(piece::piece_type::z));
    pieces.emplace_back(piece(piece::piece_type::t));

    std::random_device rd;
    std::mt19937 rng(rd());
    std::ranges::shuffle(pieces, rng);

    return pieces;
}
