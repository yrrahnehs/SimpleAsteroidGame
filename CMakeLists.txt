cmake_minimum_required(VERSION 3.20)
project(SimpleAsteroidGame)

set(CMAKE_CXX_STANDARD 20)


set(wxWidgets_ROOT_DIR </Users/harryshen/Documents/wxWidgets-3.1.5>)
set(wxWidgets_CONFIGURATION mswu)
find_package(wxWidgets COMPONENTS core base  REQUIRED)
include(${wxWidgets_USE_FILE})

set(SOURCE_FILES main.cpp main.h Frame.cpp Frame.h Gameplay.cpp Gameplay.h Player.cpp Player.h Bullet.cpp Bullet.h Enemy.cpp Enemy.h Powerup.cpp Powerup.h)
add_executable(SimpleAsteroidGame ${SOURCE_FILES})

target_link_libraries(SimpleAsteroidGame ${wxWidgets_LIBRARIES})