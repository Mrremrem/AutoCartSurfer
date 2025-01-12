#ifndef PIXEL_MANAGER_H
#define PIXEL_MANAGER_H

#include <iostream>
#include <SFML/Graphics.hpp>

#ifdef _WIN32
    #include <windows.h>
#elif defined(__linux__)
    #include <X11/Xutil.h>
#endif

/*
 * PixelManger class
 * Gets pixel color from position
 * Requirements: <SFML/Graphics.hpp>
 */
class PixelManager {
public:
    PixelManager() {}
    static sf::Color getPixelColor(sf::Vector2i position); // Get pixel color at position

};

#endif