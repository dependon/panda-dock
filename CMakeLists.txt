cmake_minimum_required(VERSION 3.5)
project(panda-dock)

set(TARGET panda-dock)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(SRCS main.cpp
               mainwindow.cpp
               mainpanel.cpp
               appscrollarea.cpp
               item/appitem.cpp
               item/blurwindow.cpp
               item/dockitem.cpp
               item/highlighteffect.cpp
               item/launcheritem.cpp
               item/trashitem.cpp
               utils/appwindowmanager.cpp
               utils/apprunthread.cpp
               utils/desktopproperties.cpp
               utils/dockitemmanager.cpp
               utils/docksettings.cpp
               utils/eventmonitor.cpp
               utils/utils.h
)

set(FORMS "")
set(RESOURCES resources.qrc)

set(QT Core Gui Widgets DBus Svg X11Extras LinguistTools)
find_package(Qt5 REQUIRED ${QT})
find_package(KF5WindowSystem)
find_package(X11 REQUIRED)

file(GLOB TS LIST_DIRECTORIES false translations/panda-dock*.ts)
set_source_files_properties(${TS} PROPERTIES OUTPUT_LOCATION ${PROJECT_SOURCE_DIR}/translations)

qt5_create_translation(QM ${allSources}  ${GLOB})

if (NOT (${CMAKE_BUILD_TYPE} MATCHES "Debug"))
    qt5_create_translation(QM ${allSources} ${TS})
endif ()


add_executable(${TARGET} ${SRCS} ${FORMS} ${RESOURCES} ${QM})
target_link_libraries(${TARGET}
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::DBus
        Qt5::Svg
        Qt5::X11Extras
        KF5::WindowSystem
        ${X11_LIBRARIES}
        ${XCOMPOSITE_LDFLAGS}
        ${XDAMAGE_LIBRARIES}
        ${XRENDER_LIBRARIES}
        -lxcb
        -lX11
        -lXtst
)

install(TARGETS ${TARGET} DESTINATION /usr/bin)

#desktop
install(FILES ${PROJECT_SOURCE_DIR}/install/panda-dock.desktop
    DESTINATION /usr/share/applications)

set(APPSHAREDIR  /usr/share/panda-dock)
#translations
install(DIRECTORY ${PROJECT_SOURCE_DIR}/translations
    DESTINATION ${APPSHAREDIR}
    FILES_MATCHING PATTERN "*.qm")

#icon
install(FILES ${PROJECT_SOURCE_DIR}/install/panda-dock.svg
    DESTINATION /usr/share/icons)
