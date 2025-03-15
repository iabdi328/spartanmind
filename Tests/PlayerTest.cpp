/**
 * @file PlayerTest.cpp
 * @author Raj Ambekar
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <Spartanmind.h>
#include <Player.h>

class TestPlayer : public Player {
public:
    TestPlayer(Spartanmind* gameWorld)
        : Player(gameWorld, L"test-image.png", L"test-image2.png") {
    }

    void Draw(wxGraphicsContext* graphics) override {
        Player::Draw(graphics);
    }

    void Eat() override {
        mDidEat = true;
    }

    void Headbutt() override {
        mBaseAngle = 0.3; // Set a test angle
        mDidHeadbutt = true;
    }

    wxPoint2DDouble GetLocation() const { return mLocation; }
    wxPoint2DDouble GetTarget() const { return mTarget; }
    double GetBaseAngle() const { return mBaseAngle; }
    double GetAuxAngle() const { return mAuxAngle; }
    bool WasEaten() const { return mDidEat; }
    bool WasHeadbutted() const { return mDidHeadbutt; }

private:
    bool mDidEat = false;
    bool mDidHeadbutt = false;
};

class PlayerTest : public ::testing::Test {
protected:
    void SetUp() override {
        mGame = new Spartanmind();
        mTestPlayer = new TestPlayer(mGame);
    }

    void TearDown() override {
        delete mTestPlayer;
        delete mGame;
    }

    Spartanmind* mGame;
    TestPlayer* mTestPlayer;
};

/**
 * Test for Player constructor
 */
TEST_F(PlayerTest, Constructor) {
    // Verify initial state after construction
    ASSERT_EQ(mTestPlayer->GetLocation().m_x, 0.0);
    ASSERT_EQ(mTestPlayer->GetLocation().m_y, 0.0);
    ASSERT_EQ(mTestPlayer->GetTarget().m_x, 0.0);
    ASSERT_EQ(mTestPlayer->GetTarget().m_y, 0.0);
    ASSERT_EQ(mTestPlayer->GetBaseAngle(), 0.0);
    ASSERT_EQ(mTestPlayer->GetAuxAngle(), 0.0);
    ASSERT_FALSE(mTestPlayer->WasEaten());
    ASSERT_FALSE(mTestPlayer->WasHeadbutted());
}

/**
 * Test for Player::SetPosition method
 */
TEST_F(PlayerTest, SetPosition)
{
    // Set player to specific position
    double x = 100.0;
    double y = 200.0;
    mTestPlayer->SetPosition(x, y);

    // Verify position was set correctly
    ASSERT_DOUBLE_EQ(mTestPlayer->GetLocation().m_x, x);
}