/**
 * @file SpartyTest.cpp
 * @author Raj Ambekar
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <Spartanmind.h>
#include <Sparty.h>

using namespace std;

class SpartyTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Create the game
        mGame = new Spartanmind();
    }

    void TearDown() override {
        delete mGame;
    }

    Spartanmind* mGame;
};

/**
 * Test for Sparty constructor
 */
TEST_F(SpartyTest, Constructor) {
    Sparty* sparty = mGame->GetPlayer();

    ASSERT_NE(sparty, nullptr) << L"Sparty should be initialized";

}