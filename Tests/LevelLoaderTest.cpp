/**
 * @file LoadLevelTest.cpp
 * @author Raj Ambekar
 */

#include <pch.h>
#include "gtest/gtest.h"

#include <LoadLevel.h>
#include <Game.h>

using namespace std;

class LevelLoaderTest : public ::testing::Test {
protected:
    void SetUp() override {
        mGame = new Game();
        mLevelLoader = new LoadLevel(mGame);
    }

    void TearDown() override {
        delete mLevelLoader;
        delete mGame;
    }

    Game* mGame;
    LoadLevel* mLevelLoader;
};


TEST_F(LevelLoaderTest, LoadLevel0) {
    mLevelLoader->Load(L"resources/levels/level0.xml");
    ASSERT_GT(mGame->GetGivens().size(), 0);
}

TEST_F(LevelLoaderTest, LoadMultipleFiles) {
    mLevelLoader->Load(L"resources/levels/level0.xml");
    size_t initialGivenCount = mGame->GetGivens().size();
    ASSERT_GT(initialGivenCount, 0);

    mLevelLoader->Load(L"resources/levels/level1.xml");
    ASSERT_GT(mGame->GetGivens().size(), 0);
}

TEST_F(LevelLoaderTest, LoadSameLevelTwice) {
    mLevelLoader->Load(L"resources/levels/level0.xml");
    size_t initialGivenCount = mGame->GetGivens().size();

    mLevelLoader->Load(L"resources/levels/level0.xml");
    ASSERT_GE(mGame->GetGivens().size(), initialGivenCount);
}