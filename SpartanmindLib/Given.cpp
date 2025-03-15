/**
 * @file Given.cpp
 * @author Daniel Conti
 */

#include "pch.h"
#include "Given.h"
#include <iostream>

Given::Given(Spartanmind* spartanmind, const std::wstring& filename,
             const wxString& id, wxString width, wxString height,
             const wxString& image, wxString value, wxString col, wxString row)
    : Letter(spartanmind, filename, id, width, height, image, value, col, row) {
    std::cout << "Given created" << std::endl;
}
