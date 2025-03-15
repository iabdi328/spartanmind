/**
 * @file LoadLevelTest.cpp
 * @author Raj Ambekar
 */

#include <pch.h>
#include "gtest/gtest.h"

#include "LoadLevel.h"
#include "Spartanmind.h"
#include "Game.h"

using namespace std;

class LevelLoaderTest : public ::testing::Test {
protected:
    void SetUp() override {
        mGame = new Game();
        mSpartanmind = new Spartanmind();
        mLevelLoader = new LoadLevel(*mSpartanmind, *mGame);
    }

    void TearDown() override {
        delete mLevelLoader;
        delete mSpartanmind;
        delete mGame;
    }

    Game* mGame;
    Spartanmind* mSpartanmind;
    LoadLevel* mLevelLoader;
};


TEST_F(LevelLoaderTest, LoadLevel0) {
    bool success = mLevelLoader->LoadFromXML(L"resources/levels/level0.xml");

    ASSERT_TRUE(success);
    //ASSERT_EQ(mSpartanmind->GetLetters().size(), 26);
    //ASSERT_EQ(mSpartanmind->GetGivens().size(), 27);

}

TEST_F(LevelLoaderTest, LoadMultipleFiles) {
    bool success = mLevelLoader->LoadFromXML(L"resources/levels/level0.xml");
    ASSERT_TRUE(success);

    size_t initialLetterCount = mSpartanmind->GetLetters().size();
    size_t initialGivenCount = mSpartanmind->GetGivens().size();

    ASSERT_GT(initialLetterCount, 0);
    ASSERT_GT(initialGivenCount, 0);

    success = mLevelLoader->LoadFromXML(L"resources/levels/level1.xml");

    if (success) {
        ASSERT_GT(mSpartanmind->GetLetters().size(), 0);
        ASSERT_GT(mSpartanmind->GetGivens().size(), 0);
    }
}

TEST_F(LevelLoaderTest, LoadSameLevelTwice) {
    bool firstLoad = mLevelLoader->LoadFromXML(L"resources/levels/level0.xml");
    ASSERT_TRUE(firstLoad);

    size_t initialLetterCount = mSpartanmind->GetLetters().size();
    size_t initialGivenCount = mSpartanmind->GetGivens().size();

    bool secondLoad = mLevelLoader->LoadFromXML(L"resources/levels/level0.xml");
    ASSERT_TRUE(secondLoad);

    ASSERT_EQ(mSpartanmind->GetLetters().size(), initialLetterCount * 2);
    ASSERT_EQ(mSpartanmind->GetGivens().size(), initialGivenCount * 2);
}