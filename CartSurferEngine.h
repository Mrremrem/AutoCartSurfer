#ifndef CART_SURFER_ENGINE_H
#define CART_SURFER_ENGINE_H

#include <SFML/Graphics.hpp>
#include "KeyboardManager.h"
#include "Direction.h"
#include "PixelManager.h"

class CartSurferEngine {
public:
    CartSurferEngine();

    void run();
    bool isRunning();
    
private:
    void handleMinecart(bool hasLeftArrow, bool hasRightArrow);
    void handleArrow();
    void flipMinecart();
    void spinMinecart();

    KeyboardManager keyboard;

    Direction minecartDirection;

    sf::Clock arrowClock;
    sf::Clock trickClock;
    bool scoreHundred;
    bool isArrowBeingProcessed;
    bool isCartDown;
    bool hasFinished;
};

#endif