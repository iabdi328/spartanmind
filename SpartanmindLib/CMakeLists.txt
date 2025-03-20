project(SpartanmindLib)

set(SOURCE_FILES
        pch.h
        MainFrame.cpp
        MainFrame.h
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
        Scoreboard.h
        Scoreboard.cpp
        Scoreboard.cpp
        Letter.cpp
        Letter.h
        Given.cpp
        Given.h
        LoadLevel.cpp
        LoadLevel.h
        Tray.cpp
        Tray.h
        Container.cpp
        Container.h
        ItemVisitor.cpp
        ItemVisitor.h
        LLetter.cpp
        LLetter.h
        PopUps.cpp
        PopUps.h
)

set(wxBUILD_PRECOMP OFF)
find_package(wxWidgets COMPONENTS core base xrc html xml REQUIRED)

include(${wxWidgets_USE_FILE})

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})