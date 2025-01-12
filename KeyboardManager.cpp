#include "KeyboardManager.h"

void KeyboardManager::pressKey(const std::string& key) {
    #ifdef _WIN32
            INPUT input = {0};
            input.type = INPUT_KEYBOARD;

            // Map key string to virtual key codes
            if (key == "Space") {
                input.ki.wVk = VK_SPACE;  // Virtual-Key Code for Space
            } else if (key == "Up") {
                input.ki.wVk = VK_UP;  // Virtual-Key Code for Down Arrow
            } else if (key == "Down") {
                input.ki.wVk = VK_DOWN;  // Virtual-Key Code for Down Arrow
            } else if (key == "Left") {
                input.ki.wVk = VK_LEFT;  // Virtual-Key Code for Left Arrow
            } else if (key == "Right") {
                input.ki.wVk = VK_RIGHT;  // Virtual-Key Code for Right Arrow
            } else {
                std::cerr << "Unsupported key: " << key << std::endl;
                return;
            }

            // Simulates key hold
            SendInput(1, &input, sizeof(INPUT));
            pressedKeys.push_back(input.ki.wVk);
    #elif defined(__linux__)
            Display* display = XOpenDisplay(nullptr);
            if (!display) {
                std::cerr << "Failed to open X display for key press!" << std::endl;
                return;
            }

            KeySym keysym;
            if (key == "Space") {
                keysym = XK_space;
            } else if (key == "Up") {
                keysym = XK_Up;
            } else if (key == "Down") {
                keysym = XK_Down;
            } else if (key == "Left") {
                keysym = XK_Left;
            } else if (key == "Right") {
                keysym = XK_Right;
            } else {
                std::cerr << "Unsupported key: " << key << std::endl;
                XCloseDisplay(display);
                return;
            }

            KeyCode keyCode = XKeysymToKeycode(display, keysym);
            if (!keyCode) {
                std::cerr << "Failed to map KeySym to KeyCode!" << std::endl;
                XCloseDisplay(display);
                return;
            }

            // Simulates key hold
            XTestFakeKeyEvent(display, keyCode, True, 0);
            XFlush(display);  // Ensure the event is sent

            pressedKeys.push_back(keyCode);

            XCloseDisplay(display);
    #else
            std::cerr << "Unsupported platform for key simulation!" << std::endl;
    #endif
}

void KeyboardManager::releaseAllKeys() {
    #ifdef _WIN32
        for (int keyCode : pressedKeys) {
            INPUT input = {0};
            input.type = INPUT_KEYBOARD;
            input.ki.wVk = keyCode;
            input.ki.dwFlags = KEYEVENTF_KEYUP;  // Release the key
            SendInput(1, &input, sizeof(INPUT));
        }
    #elif defined(__linux__)
            Display* display = XOpenDisplay(nullptr);
            if (!display) {
                std::cerr << "Failed to open X display for key release!" << std::endl;
                return;
            }

            for (KeyCode keyCode : pressedKeys) {
                XTestFakeKeyEvent(display, keyCode, False, 0);  // Key release
                XFlush(display);  // Ensure the event is sent
            }

            XCloseDisplay(display);
    #else
            std::cerr << "Unsupported platform for key simulation!" << std::endl;
    #endif
    // Clear the pressed keys list
    pressedKeys.clear();
}