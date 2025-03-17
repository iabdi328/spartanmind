/**
 * @file Given.cpp
 * @author Daniel Conti
 */

#include "pch.h"
#include "Given.h"
#include <iostream>

Given::Given(Game* game, const std::wstring& filename,
             const wxString& id, wxString width, wxString height,
             const wxString& image, wxString value, wxString col, wxString row)
    : Letter(game, filename, id, width, height, image, value, col, row) {
    //std::cout << "Given created" << std::endl;
}
