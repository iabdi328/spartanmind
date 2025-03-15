/**
 * @file ScoreboardTest.cpp
 * @author Raj Ambekar
 */

#include <pch.h>
#include <gtest/gtest.h>
#include <Scoreboard.h>

class ScoreboardTest : public ::testing::Test {
protected:
    void SetUp() override {
        scoreboard = new Scoreboard();
    }

    Scoreboard* scoreboard;
};

/**
 * Test for Scoreboard constructor
 */
TEST_F(ScoreboardTest, Constructor) {
    ASSERT_EQ(scoreboard->GetElapsedTime(), 0.0);
}

/**
 * Test for Scoreboard::Update method
 */
TEST_F(ScoreboardTest, UpdateTime) {
    scoreboard->Update(10.0);
    ASSERT_EQ(scoreboard->GetElapsedTime(), 10.0);

    scoreboard->Update(5.5);
    ASSERT_EQ(scoreboard->GetElapsedTime(), 15.5);
}

/**
 * Test for Scoreboard::Update with zero time
 */
TEST_F(ScoreboardTest, UpdateZeroTime) {
    scoreboard->Update(0.0);
    ASSERT_EQ(scoreboard->GetElapsedTime(), 0.0);
}