#pragma once

#include "piece.h"
#include "playfield.h"

class i_piece : public piece
{
    public:
        i_piece(const playfield& field);

        bool can_rotate(rotation r) override;
        void rotate(rotation r) override;
    private:
        void set_blocks(rotation r);
};

class j_piece : public piece
{
    public:
        j_piece(const playfield& field);

        bool can_rotate(rotation r) override;
        void rotate(rotation r) override;
    private:
        void set_blocks(rotation r);
};

class l_piece : public piece
{
    public:
        l_piece(const playfield& field);

        bool can_rotate(rotation r) override;
        void rotate(rotation r) override;
    private:
        void set_blocks(rotation r);
};

class o_piece : public piece
{
    public:
        o_piece(const playfield& field);

        bool can_rotate(rotation r) override;
        void rotate(rotation r) override;
};

class s_piece : public piece
{
    public:
        s_piece(const playfield& field);

        bool can_rotate(rotation r) override;
        void rotate(rotation r) override;
    private:
        void set_blocks(rotation r);
};

class z_piece : public piece
{
    public:
        z_piece(const playfield& field);

        bool can_rotate(rotation r) override;
        void rotate(rotation r) override;
    private:
        void set_blocks(rotation r);
};

class t_piece : public piece
{
    public:
        t_piece(const playfield& field);

        bool can_rotate(rotation r) override;
        void rotate(rotation r) override;
    private:
        void set_blocks(rotation r);
};
