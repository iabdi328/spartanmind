/**
 * @file SpartanmindTest.cpp
 * @author Raj Ambekar
 */


#include <pch.h>
#include "gtest/gtest.h"
#include <Spartanmind.h>
#include <Sparty.h>
#include <wx/filename.h>

using namespace std;

class SpartanmindTest : public ::testing::Test {
protected:
    /**
    * Create a path to a place to put temporary files
    */
    wxString TempPath()
    {
        // Create a temporary filename we can use
        auto path = wxFileName::GetTempDir() + L"/spartanmind";
        if(!wxFileName::DirExists(path))
        {
            wxFileName::Mkdir(path);
        }

        return path;
    }
};

TEST_F(SpartanmindTest, Construct){
    Spartanmind spartanmind;

    ASSERT_NE(spartanmind.GetPlayer(), nullptr) << L"Player should be initialized";
}

TEST_F(SpartanmindTest, Player) {
    Spartanmind spartanmind;

    Sparty* player = spartanmind.GetPlayer();

    ASSERT_NE(player, nullptr) << L"Player should not be null";

    // Test that we can get the same player instance
    ASSERT_EQ(spartanmind.GetPlayer(), player) << L"Should return the same player instance";
}

