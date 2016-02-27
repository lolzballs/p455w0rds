cmake_minimum_required(VERSION 3.3)
project(p455w0rds CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

set(SOURCE src/main.cpp src/window.cpp src/window.h src/new_password_dialog.cpp src/new_password_dialog.h)

find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Network REQUIRED)
find_package(Qt5Sql REQUIRED)
find_package(Threads REQUIRED)

include_directories(
        ${Qt5Gui_INCLUDE_DIRS}
        ${Qt5Gui_PRIVATE_INCLUDE_DIRS}
        ${Qt5Widgets_INCLUDE_DIRS}
        ${Qt5Core_INCLUDE_DIRS}
)

add_executable(p455w0rds ${SOURCE})

target_link_libraries(p455w0rds
        Qt5::Widgets
        Qt5::Core
        Qt5::Gui
        ${CMAKE_THREAD_LIBS_INIT}
        )

if(WIN32)
    target_link_libraries(p455w0rds
            user32.lib
            gdi32.lib
            dwmapi.lib
            )
endif()

# --- RUNTIME DEPENDENCIES ---
# Only necessary on Windows.

if(WIN32)
    find_program(WINDEPLOY windeployqt PATHS ${Qt5Core_DIR}/../../../bin NO_DEFAULT_PATH)

    if (WINDEPLOY)
        add_custom_command(TARGET p455w0rds POST_BUILD
                # Call windeployqt to copy necessary dependencies into the executable path.
                COMMAND CMD /C "SET PATH=%PATH%;${QT_DIR}/bin && ${WINDEPLOY} $<$<OR:$<CONFIG:Release>,$<CONFIG:MinSizeRel>,$<CONFIG:RelWithDebInfo>>:--release> --no-translations $<TARGET_FILE:p455w0rds>"
                )
    else()
        message(WARNING "Unable to find Qt Windows deployment tool at ${Qt5Core_DIR}/../../../bin, no runtime dependencies will be copied.")
    endif()
endif()
