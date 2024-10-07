#pragma once

#include "piece.h"

class i_piece : public piece
{
    public:
        i_piece();

        void rotate(rotation r) override;
    private:
        void set_blocks(rotation r);
};

class j_piece : public piece
{
    public:
        j_piece();

        void rotate(rotation r) override;
};

class l_piece : public piece
{
    public:
        l_piece();

        void rotate(rotation r) override;
};

class o_piece : public piece
{
    public:
        o_piece();

        void rotate(rotation r) override;
};

class s_piece : public piece
{
    public:
        s_piece();

        void rotate(rotation r) override;
};

class z_piece : public piece
{
    public:
        z_piece();

        void rotate(rotation r) override;
};

class t_piece : public piece
{
    public:
        t_piece();

        void rotate(rotation r) override;
};
