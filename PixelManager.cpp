#include "PixelManager.h"
/*
 * Cross platform way to get pixel color
 * Pre: none
 * Post:
 *      Returns sf::Color code of pixel at position if window system allows
 *      Returns sf::Black and std::err otherwise
 */
sf::Color PixelManager::getPixelColor(sf::Vector2i position) {
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
