/**
 * @file gtest_main.cpp
 * @author Raj Ambekar
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <wx/filefn.h>

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);

    wxSetWorkingDirectory(L"..");
    wxInitAllImageHandlers();

	// Initialize wxWidgets
	if (!wxInitialize()) {
		return -1; // Failed to initialize wxWidgets
	}

	// Run all tests
	int result = RUN_ALL_TESTS();

	// Uninitialize wxWidgets
	wxUninitialize();
	return result;
}