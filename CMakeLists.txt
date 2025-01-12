cmake_minimum_required(VERSION 3.10)  # Specify the minimum version of CMake

# Set the project name
project(AutoCartSurfer)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find SFML package
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Include directories for X11
find_package(X11 REQUIRED)

# Add the executable
add_executable(AutoCartSurfer AutoCartSurfer.cpp KeyboardManager.cpp PixelManager.cpp
               CartSurferEngine.cpp)

# Link the libraries
target_link_libraries(AutoCartSurfer 
    sfml-graphics 
    sfml-window 
    sfml-system 
    ${X11_LIBRARIES} 
    Xtst
)

# Include directories for X11
target_include_directories(AutoCartSurfer PRIVATE ${X11_INCLUDE_DIR})
