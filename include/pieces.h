#pragma once

#include "piece.h"

class i_piece : public piece
{
    public:
        i_piece();

        bool can_rotate(rotation r, const playfield& field) override;
        void rotate(rotation r) override;
    private:
        void set_blocks(rotation r);
};

class j_piece : public piece
{
    public:
        j_piece();

        bool can_rotate(rotation r, const playfield& field) override;
        void rotate(rotation r) override;
    private:
        void set_blocks(rotation r);
};

class l_piece : public piece
{
    public:
        l_piece();

        bool can_rotate(rotation r, const playfield& field) override;
        void rotate(rotation r) override;
    private:
        void set_blocks(rotation r);
};

class o_piece : public piece
{
    public:
        o_piece();

        bool can_rotate(rotation r, const playfield& field) override;
        void rotate(rotation r) override;
};

class s_piece : public piece
{
    public:
        s_piece();

        bool can_rotate(rotation r, const playfield& field) override;
        void rotate(rotation r) override;
    private:
        void set_blocks(rotation r);
};

class z_piece : public piece
{
    public:
        z_piece();

        bool can_rotate(rotation r, const playfield& field) override;
        void rotate(rotation r) override;
    private:
        void set_blocks(rotation r);
};

class t_piece : public piece
{
    public:
        t_piece();

        bool can_rotate(rotation r, const playfield& field) override;
        void rotate(rotation r) override;
    private:
        void set_blocks(rotation r);
};
