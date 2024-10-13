#include "autorepeat.h"

#include <gtest/gtest.h>

#include <vector>

class autorepeat_test : public testing::Test
{
    public:
        std::deque<input_event> events;
        autorepeat repeat;
        std::vector<input_event> possible_events
        {
            input_event::hard_drop,
            input_event::move_piece_left,
            input_event::move_piece_right,
            input_event::soft_drop,
            input_event::rotate_clockwise,
            input_event::rotate_counterclockwise,
        };

    private:
        void SetUp() override
        {
            repeat = autorepeat();
        }
};

TEST_F(autorepeat_test, if_no_prior_events_exist_then_autorepeat_should_happen)
{
    for (input_event e : possible_events)
    {
        EXPECT_TRUE(repeat.should_autorepeat(e));
    }
}

TEST_F(autorepeat_test, autorepeats_if_no_delay_or_tickrate_is_set)
{
    repeat.set_delay(1);
    repeat.set_tickrate(1);

    repeat.start_processing();
    for (input_event e : possible_events)
    {
        EXPECT_TRUE(repeat.should_autorepeat(e));
    }

    repeat.start_processing();
    for (input_event e : possible_events)
    {
        EXPECT_TRUE(repeat.should_autorepeat(e));
    }
}

TEST_F(autorepeat_test, autorepeats_according_to_tickrate)
{
    repeat.set_delay(1);
    repeat.set_tickrate(2);

    repeat.start_processing();
    for (input_event e : possible_events)
    {
        EXPECT_TRUE(repeat.should_autorepeat(e));
    }

    repeat.start_processing();
    for (input_event e : possible_events)
    {
        EXPECT_FALSE(repeat.should_autorepeat(e));
    }
    
    repeat.start_processing();
    for (input_event e : possible_events)
    {
        EXPECT_TRUE(repeat.should_autorepeat(e));
    }
}

TEST_F(autorepeat_test, double_tapping_is_possible)
{
    repeat.set_delay(12);
    repeat.set_tickrate(2);

    repeat.start_processing();
    EXPECT_TRUE(repeat.should_autorepeat(possible_events.at(0)));

    repeat.start_processing();

    repeat.start_processing();
    EXPECT_TRUE(repeat.should_autorepeat(possible_events.at(0)));
}

TEST_F(autorepeat_test, does_not_autorepeat_if_delay_is_not_met)
{
    repeat.set_delay(12);
    repeat.set_tickrate(1);

    repeat.start_processing();
    ASSERT_TRUE(repeat.should_autorepeat(possible_events.at(0)));

    for (int i = 0; i < 11; ++i)
    {
        repeat.start_processing();
        EXPECT_FALSE(repeat.should_autorepeat(possible_events.at(0)));
    }
}

TEST_F(autorepeat_test, after_delay_is_met_tickrate_is_used)
{
    repeat.set_delay(3);
    repeat.set_tickrate(2);

    repeat.start_processing();
    ASSERT_TRUE(repeat.should_autorepeat(possible_events.at(0)));

    for (int i = 0; i < 2; ++i)
    {
        repeat.start_processing();
        ASSERT_FALSE(repeat.should_autorepeat(possible_events.at(0)));
    }

    repeat.start_processing();
    EXPECT_TRUE(repeat.should_autorepeat(possible_events.at(0)));

    repeat.start_processing();
    EXPECT_FALSE(repeat.should_autorepeat(possible_events.at(0)));

    repeat.start_processing();
    EXPECT_TRUE(repeat.should_autorepeat(possible_events.at(0)));
}
