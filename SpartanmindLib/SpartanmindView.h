/**
* @file SpartanmindView.h
 * @author Raj Ambekar
 */

#ifndef PROJECT1_SPARTANMINDLIB_SPARTANMINDVIEW_H
#define PROJECT1_SPARTANMINDLIB_SPARTANMINDVIEW_H

#include <wx/wx.h>
#include "Game.h"
#include "LoadLevel.h"
#include <wx/stopwatch.h>

/**
 * View class for displaying the Spartanmind game
 */
class SpartanmindView : public wxWindow
{
private:
    /// Game object for virtual-pixel handling
    Game mGame;
    /// Timer for periodic updates
	wxTimer* mGameTimer = nullptr;

    ///Grabbed Item
    std::shared_ptr<Item> mGrabbedItem = nullptr;

    /// Game Active
    bool mGameIsActive;
    ///New level
    bool mNewLevel = false;

    /// The last stopwatch time
    long mTime = 0;

    double mAllTime;
    /// StopWatch instance
    wxStopWatch mStopWatch;

	void OnPaint(wxPaintEvent& event);
	void OnKeyDown(wxKeyEvent& event);
	void OnTimer(wxTimerEvent& event);

public:
	    /**
     * @brief Contains the slot positions for level zero.
     * Each pair represents grid coordinates for level zero slots.
     */
    std::vector<std::pair<int, int>> mLevelZeroSlots = {
        {7, 4},
        {8, 4},
        {9, 4},
        {10, 4},
        {11, 4},
        {12, 4},
    };

    /**
     * @brief Contains the slot positions for level one.
     * Each pair represents grid coordinates for level one slots.
     */
    std::vector<std::pair<int, int>> mLevelOneSlots = {
        {7, 4},
        {8, 4},
        {9, 4},
        {10, 4},
        {11, 4},
        {12, 4},
    };

    /**
     * @brief Contains the slot positions for level two.
     * Each pair represents grid coordinates for level two slots.
     */
    std::vector<std::pair<int, int>> mLevelTwoSlots = {
        {11, 6},
        {12, 6},
        {13, 6},
        {14, 6},
        {15, 6},
        {16, 6},
        {17, 6},
        {18, 6}
    };

    /**
     * @brief Contains the slot positions for level three.
     * Each pair represents grid coordinates for level three slots.
     */
    std::vector<std::pair<int, int>> mLevelThreeSlots = {
        {7, 4},
        {8, 4},
        {9, 4},
        {10, 4},
        {11, 4},
        {12, 4},
    };

    ~SpartanmindView();
    void Initialize(wxFrame* parent);
    void OnMouseClick(wxMouseEvent& event);
    void OnLevelZero(wxCommandEvent& event);
    void OnLevelOne(wxCommandEvent &event);
    void OnLevelTwo(wxCommandEvent &event);
    void OnLevelThree(wxCommandEvent &event);
    void LoadNextLevel();
    void NewLevel(const wxString &filename, int levelNumber);
    void Remove10Seconds();


};

#endif // PROJECT1_SPARTANMINDLIB_SPARTANMINDVIEW_H