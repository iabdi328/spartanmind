/**
 * @file SpartanmindTest.cpp
 * @author Raj Ambekar
 */


#include <pch.h>
#include "gtest/gtest.h"
#include <Game.h>
#include <Player.h>
#include <wx/filename.h>

using namespace std;

class SpartanmindTest : public ::testing::Test {
protected:
    wxString TempPath()
    {
        auto path = wxFileName::GetTempDir() + L"/spartanmind";
        if(!wxFileName::DirExists(path))
        {
            wxFileName::Mkdir(path);
        }

        return path;
    }
};

TEST_F(SpartanmindTest, Construct){
    Game spartanmind;

    ASSERT_NE(spartanmind.GetPlayer(), nullptr) << L"Player should be initialized";
}

TEST_F(SpartanmindTest, Player) {
    Game spartanmind;

    std::shared_ptr<Player> player = spartanmind.GetPlayer();

    ASSERT_NE(player, nullptr) << L"Player should not be null";

    ASSERT_EQ(spartanmind.GetPlayer(), player) << L"Should return the same player instance";
}

