project(SpartanmindLib)

set(SOURCE_FILES
        pch.h
        MainFrame.cpp
        MainFrame.h
        Spartanmind.cpp
        Spartanmind.h
        SpartanmindView.cpp
        SpartanmindView.h
        ids.h)

set(wxBUILD_PRECOMP OFF)
find_package(wxWidgets COMPONENTS core base xrc html xml REQUIRED)

include(${wxWidgets_USE_FILE})

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})