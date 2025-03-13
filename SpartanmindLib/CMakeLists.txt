project(SpartanmindLib)

set(SOURCE_FILES
        pch.h
        MainFrame.cpp
        MainFrame.h
        Spartanmind.cpp
        Spartanmind.h
        SpartanmindView.cpp
        SpartanmindView.h
        ids.h
        Game.h
        Game.cpp
        Game.cpp
        Item.cpp
        Item.h
        Player.cpp
        Player.h
        Sparty.cpp
        Scoreboard.h
        Scoreboard.cpp
        Scoreboard.cpp
        Letter.cpp
        Letter.h
)

set(wxBUILD_PRECOMP OFF)
find_package(wxWidgets COMPONENTS core base xrc html xml REQUIRED)

include(${wxWidgets_USE_FILE})

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})