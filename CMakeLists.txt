cmake_minimum_required(VERSION 3.10)

project(AutoCartSurfer)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

find_package(X11 REQUIRED)

add_executable(AutoCartSurfer AutoCartSurfer.cpp KeyboardManager.cpp PixelManager.cpp
               CartSurferEngine.cpp)

target_link_libraries(AutoCartSurfer 
    sfml-graphics 
    sfml-window 
    sfml-system 
    ${X11_LIBRARIES} 
    Xtst
)

target_include_directories(AutoCartSurfer PRIVATE ${X11_INCLUDE_DIR})
