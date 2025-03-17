/**
 * @file SpartyTest.cpp
 * @author raj, Emmanuel koshy
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <Spartanmind.h>
#include <Sparty.h>

using namespace std;

class SpartyTest : public ::testing::Test {
protected:
    void SetUp() override {
        mGame = new Spartanmind();
    }

    void TearDown() override {
        delete mGame;
    }

    Spartanmind* mGame;
};

TEST_F(SpartyTest, Constructor) {
    Sparty* sparty = mGame->GetPlayer();

    ASSERT_NE(sparty, nullptr) << L"Sparty should be initialized";

}