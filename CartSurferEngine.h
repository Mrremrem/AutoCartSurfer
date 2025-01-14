#ifndef CART_SURFER_ENGINE_H
#define CART_SURFER_ENGINE_H

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include "KeyboardManager.h"
#include "Direction.h"
#include "PixelManager.h"

class CartSurferEngine {
public:
    CartSurferEngine(sf::Vector2i LEFT_ARROW_POS, sf::Vector2i RIGHT_ARROW_POS, 
                    sf::Vector2i COINS_EARNED_SCREEN_POS);

    void run();
    bool isRunning();
    
private:
    void handleMinecart(bool hasLeftArrow, bool hasRightArrow);
    void handleArrow();
    void flipMinecart();
    void spinMinecart();

    KeyboardManager keyboard;

    Direction minecartDirection;

    sf::Vector2i LEFT_ARROW_POS; // Left arrow position
    sf::Vector2i RIGHT_ARROW_POS; // Right arrow position
    sf::Vector2i COINS_EARNED_SCREEN_POS; // Coins earned screen position

    sf::Clock arrowClock;
    sf::Clock trickClock;
    bool scoreHundred;
    bool isArrowBeingProcessed;
    bool isCartDown;
    bool hasFinished;
};

#endif