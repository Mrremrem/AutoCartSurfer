#include <SFML/Graphics.hpp>
#include "KeyboardManager.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>

#ifdef _WIN32
    #include <windows.h>
#elif defined(__linux__)
    #include <X11/Xlib.h>
    #include <X11/Xutil.h>
    #include <X11/extensions/XTest.h>  // Include this for XTest functions
#endif
/*
 * Cross platform way to get pixel color
 * Pre: none
 * Post:
 *      Returns sf::Color code of pixel at position if window system allows
 *      Returns sf::Black and std::err otherwise
 */
sf::Color getPixelColor(sf::Vector2i position) {
#ifdef _WIN32
    HDC hdc = GetDC(nullptr);  // Gets device context/default display (like :0)
    COLORREF color = GetPixel(hdc, position.x, position.y); // Gets pixel color
    ReleaseDC(nullptr, hdc);  // Closes default display

    return sf::Color(GetRValue(color), GetGValue(color), GetBValue(color));
#elif defined(__linux__)
    // Apologies Wayland users, I haven't learned Wayland's window system yet !!!
    Display* display = XOpenDisplay(nullptr);  // Connects to display :0
    if (!display) {
        std::cerr << "Failed to open X display!" << std::endl;
        return sf::Color::Black;
    }

    Window root = DefaultRootWindow(display);  // Get the root window
    XImage* image = XGetImage(display, root, position.x, position.y, 1, 1, AllPlanes, ZPixmap);
    if (!image) {
        std::cerr << "Failed to get image from X server!" << std::endl;
        XCloseDisplay(display);
        return sf::Color::Black;
    }

    // Extracts RGB from pixel
    unsigned long pixel = XGetPixel(image, 0, 0);
    int red = (pixel & image->red_mask) >> 16;
    int green = (pixel & image->green_mask) >> 8;
    int blue = (pixel & image->blue_mask);

    XDestroyImage(image);  // Frees the XImage
    XCloseDisplay(display);  // Closes default display

    return sf::Color(red, green, blue);
#else
    // Unsupported platform
    std::cerr << "Unsupported platform!" << std::endl;
    return sf::Color::Black;
#endif
}

/*
 * Provides directions for minecart
 * Pre: None
 * Post: None
 */
enum class Direction {
    Forward,
    Left,
    Right,
};

int main() {
    sf::RenderWindow window(sf::VideoMode(1920, 1200), "Auto CartSurfer");
    window.setFramerateLimit(60);

    KeyboardManager keyboard;


    bool scoreHundred = true;
    sf::Clock clock;
    bool isArrowBeingProcessed = false;
    Direction cartDirection = Direction::Forward;
    bool isCartDown = false;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Constants
        const sf::Color BLACK(0, 0, 0); // Color for arrow
        const sf::Color BLUE(2, 128, 205); // Color for coin screen
        const sf::Vector2i LEFT_ARROW(343, 769); // Left arrow position
        const sf::Vector2i RIGHT_ARROW(1499, 698); // Right arrow position
        const sf::Vector2i COINS_EARNED_SCREEN(1184, 448); // Coins earned screen position
        // Tests if cart must go left, right, or game has finished
        bool hasLeftArrow = getPixelColor(LEFT_ARROW) == BLACK;
        bool hasRightArrow = getPixelColor(RIGHT_ARROW) == BLACK;
        bool hasFinished = getPixelColor(COINS_EARNED_SCREEN) == BLUE;

        // Time to process arrows, ignore all
        if (!isArrowBeingProcessed && (hasLeftArrow || hasRightArrow)) {
            if (hasLeftArrow) {
                cartDirection = Direction::Right;
            } else {
                cartDirection = Direction::Left;
            }

            isArrowBeingProcessed = true;
            keyboard.releaseAllKeys();

            clock.restart();
        }




        if (isArrowBeingProcessed) {
            if (!isCartDown && clock.getElapsedTime().asMilliseconds() > 600) {
                keyboard.pressKey("Down");
                isCartDown = true;
            }
            
            if (clock.getElapsedTime().asMilliseconds() > 650) {
                if (cartDirection == Direction::Left) {
                    keyboard.pressKey("Left");
                } else {
                    keyboard.pressKey("Right");
                }
            }

            if (clock.getElapsedTime().asMilliseconds() > 2150) {
                keyboard.releaseAllKeys();
                isCartDown = false;
                isArrowBeingProcessed = false;
                cartDirection = Direction::Forward;
                clock.restart();
            }
        } 
        
        if (scoreHundred && !isArrowBeingProcessed) {
            if (!isCartDown && clock.getElapsedTime().asMilliseconds() % 1000 < 600) {
                keyboard.pressKey("Down");
            } else if (clock.getElapsedTime().asMilliseconds() % 1000  < 650) {
                keyboard.pressKey("Space");
                keyboard.releaseAllKeys();
            } else if (clock.getElapsedTime().asMicroseconds() % 1000  < 1000) {
                scoreHundred = false;
                keyboard.releaseAllKeys();
            }
        } 
        
        if (!scoreHundred && !isArrowBeingProcessed) {
            if (!isCartDown && clock.getElapsedTime().asMilliseconds() % 1100 < 600) {
                keyboard.pressKey("Space");
            } else if (clock.getElapsedTime().asMilliseconds() % 1100  < 650) {
                keyboard.pressKey("Right");
                keyboard.releaseAllKeys();
            } else if (clock.getElapsedTime().asMicroseconds() % 1100  < 1100) {
                scoreHundred = true;
                keyboard.releaseAllKeys();
            }
        } 
        
        if (hasFinished) {
            return 0;
        }

        window.clear(sf::Color::Magenta);
        window.display();
    }
}
