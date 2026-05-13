/**
 * @file SpartyTest.cpp
 * @author raj, Emmanuel koshy
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <Game.h>
#include <Player.h>

using namespace std;

class SpartyTest : public ::testing::Test {
protected:
    void SetUp() override {
        mGame = new Game();
    }

    void TearDown() override {
        delete mGame;
    }

    Game* mGame;
};

TEST_F(SpartyTest, Constructor) {
    std::shared_ptr<Player> sparty = mGame->GetPlayer();

    ASSERT_NE(sparty, nullptr) << L"Sparty should be initialized";

}