#ifndef KEYBOARD_MANAGER_H
#define KEYBOARD_MANAGER_H

#include <iostream>
#include <vector>
#include <string>

#ifdef _WIN32
    #include <windows.h>
#elif defined(__linux__)
    #include <X11/Xutil.h>
    #include <X11/extensions/XTest.h>
#endif

/*
 * Simulates pressing a key
 * Pre: none
 * Post: Presses key from std::string& key
 */
class KeyboardManager {
public:
    KeyboardManager() {};

    ~KeyboardManager() {
        releaseAllKeys();
    }

    // Press a key (keeps it held down)
    void pressKey(const std::string& key);

    // Release all keys (simulated key release)
    void releaseAllKeys();

private:
    std::vector<int> pressedKeys;  // Store pressed key codes
};

#endif