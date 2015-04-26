cmake_minimum_required(VERSION 3.1)
project(jumponthings)

# Setting up the project.
set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/build")
set(   LIBRARY_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/build")
set(CMAKE_CXX_FLAGS "-Wall -O2 -std=c++11 ${CMAKE_CXX_FLAGS}")

# Setting up the executable.
set(SOURCES src/texablerender.cpp
            src/collidable.cpp
            src/texableset.cpp
            src/rectangle.cpp
            src/player.cpp
            src/game.cpp
            src/main.cpp)

add_executable(jumponthings ${SOURCES})

# Adding the library.
find_package(clibgame REQUIRED)
include_directories(${CLIBGAME_INCLUDE_DIRS})
target_link_libraries(jumponthings ${CLIBGAME_LIBRARIES})
