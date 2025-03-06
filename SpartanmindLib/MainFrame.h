/**
 * @file MainFrame.h
 * @author Raj Ambekar
 *
 * The top-level (main) frame of the application
 */

#ifndef PROJECT1_SPARTANMINDLIB_MAINFRAME_H
#define PROJECT1_SPARTANMINDLIB_MAINFRAME_H

/**
 * The top-level (main) frame of the application
 */
class MainFrame : public wxFrame
{
private:

public:
    void Initialize();
    void OnExit(wxCommandEvent& event);

};

#endif //PROJECT1_SPARTANMINDLIB_MAINFRAME_H
