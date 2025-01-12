#ifndef KEYBOARD_MANAGER_H
#define KEYBOARD_MANAGER_H

#include <iostream>
#include <vector>
#include <string>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/extensions/XTest.h>

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