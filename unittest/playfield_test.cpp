#include "playfield.h"

#include "constants.h"

#include <gtest/gtest.h>

#include <memory>

class playfield_test : public testing::Test
{
    protected:
        const int width = 10;
        const int height = 20;
        std::unique_ptr<playfield> field = nullptr;

        void set_line_of_tiles(int line)
        {
            for (int x = 0; x < width; ++x)
            {
                field->set_tile(x, line, light_blue);
            }

            assert_line_has_tiles(line);
        }

        bool is_field_empty()
        {
            bool is_empty = true;
            for (int y = 0; y < height; ++y)
            {
                for (int x = 0; x < width; ++x)
                {
                    if (field->get_tile(x, y).has_shape)
                    {
                        is_empty = false;
                        break;
                    }
                }

                if (!is_empty)
                {
                    break;
                }
            }

            return is_empty;
        }
        

    private:
        void SetUp() override
        {
            field = std::make_unique<playfield>(width, height);
        }

        void assert_line_has_tiles(int line)
        {
            for (int x = 0; x < width; ++x)
            {
                ASSERT_TRUE(field->get_tile(x, line).has_shape);
            }
        }
};

TEST_F(playfield_test, field_is_initially_empty)
{
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            EXPECT_FALSE(field->get_tile(x, y).has_shape);
        }
    }
}

TEST_F(playfield_test, clearing_only_line_leaves_field_empty)
{
    int y = height - 1;
    set_line_of_tiles(y);

    field->clear_line(y);

    EXPECT_TRUE(is_field_empty());
}

TEST_F(playfield_test, tiles_above_cleared_line_are_moved_down)
{
    int y = height - 1;
    set_line_of_tiles(y);
    
    int line_above = y - 1;
    std::vector<int> xs{1, 5, 7};
    for (int x : xs)
    {
        field->set_tile(x, line_above, light_blue);
    }

    field->clear_line(y);

    for (int x : xs)
    {
        EXPECT_TRUE(field->get_tile(x, y).has_shape);
    }
}

TEST_F(playfield_test, multiple_lines_are_cleared)
{
    int y = height - 1;
    set_line_of_tiles(y);
    set_line_of_tiles(y - 1);

    field->clear_line(y - 1);
    field->clear_line(y);

    EXPECT_TRUE(is_field_empty());
}

TEST_F(playfield_test, pieces_move_down_correct_amount)
{
    int y = height - 1;
    set_line_of_tiles(y);
    field->set_tile(0, y - 1, light_blue);
    field->set_tile(0, y - 2, light_blue);
    field->set_tile(1, y - 2, light_blue);
    field->set_tile(2, y - 2, light_blue);

    field->clear_line(y);
    
    EXPECT_TRUE(field->get_tile(0, y).has_shape);
    EXPECT_TRUE(field->get_tile(0, y - 1).has_shape);
    EXPECT_TRUE(field->get_tile(1, y - 1).has_shape);
    EXPECT_TRUE(field->get_tile(2, y - 1).has_shape);
}
