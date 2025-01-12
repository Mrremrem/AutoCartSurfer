#include "CartSurferEngine.h"
#include <cmath>

CartSurferEngine::CartSurferEngine(){
    scoreHundred = true;
    isArrowBeingProcessed = false;
    Direction cartDirection = Direction::Forward;
    isCartDown = false;
    hasFinished = false;
}

void CartSurferEngine::run() {
    // Position constants
    const sf::Color BLACK(0, 0, 0); // Color for arrow
    const sf::Color BLUE(2, 128, 205); // Color for coin screen
    const sf::Vector2i LEFT_ARROW(343, 769); // Left arrow position
    const sf::Vector2i RIGHT_ARROW(1499, 698); // Right arrow position
    const sf::Vector2i COINS_EARNED_SCREEN(1184, 448); // Coins earned screen position

    // Tests if cart must go left, right, or game has finished
    bool hasLeftArrow = PixelManager::getPixelColor(LEFT_ARROW) == BLACK;
    bool hasRightArrow = PixelManager::getPixelColor(RIGHT_ARROW) == BLACK;
    hasFinished = PixelManager::getPixelColor(COINS_EARNED_SCREEN) == BLUE;

    if (!hasFinished) {
        handleMinecart(hasLeftArrow, hasRightArrow);
    }
}

void CartSurferEngine::handleMinecart(bool hasLeftArrow, bool hasRightArrow) {
    // Time to process arrows, ignore all
    if (!isArrowBeingProcessed && (hasLeftArrow || hasRightArrow)) {
        if (hasLeftArrow) {
            minecartDirection = Direction::Right;
        } else {
            minecartDirection = Direction::Left;
        }

        isArrowBeingProcessed = true;
        keyboard.releaseAllKeys();

        arrowClock.restart();
    }

    // Starts handling arrow if needed
    if (isArrowBeingProcessed) {
        handleArrow();
    } 
    
    if (scoreHundred && !isArrowBeingProcessed) {
        flipMinecart();
    } 
    
    if (!scoreHundred && !isArrowBeingProcessed) {
        spinMinecart();
    }
}

bool CartSurferEngine::isRunning() {
    return !hasFinished;
}

void CartSurferEngine::handleArrow() {
    if (!isCartDown && arrowClock.getElapsedTime().asMilliseconds() > 600) {
        keyboard.pressKey("Down");
        isCartDown = true;
    }
    
    if (arrowClock.getElapsedTime().asMilliseconds() > 650) {
        if (minecartDirection == Direction::Left) {
            keyboard.pressKey("Left");
        } else {
            keyboard.pressKey("Right");
        }
    }

    if (arrowClock.getElapsedTime().asMilliseconds() > 2150) {
        keyboard.releaseAllKeys();
        isCartDown = false;
        isArrowBeingProcessed = false;
        minecartDirection = Direction::Forward;
        arrowClock.restart();
        trickClock.restart();
    }
}

void CartSurferEngine::flipMinecart() {
    const int MAX_MILLISECONDS_FOR_FLIP = 1000;
    const int MAX_MINECART_DOWN_TIME = 600;
    const int MAX_MINECART_JUMP_TIME = 650;
    if (!isCartDown && trickClock.getElapsedTime().asMilliseconds() % MAX_MILLISECONDS_FOR_FLIP
            < MAX_MINECART_DOWN_TIME) {
        keyboard.pressKey("Down");
    } else if (trickClock.getElapsedTime().asMilliseconds() % MAX_MILLISECONDS_FOR_FLIP
            < MAX_MINECART_JUMP_TIME) {
        keyboard.pressKey("Space");
        keyboard.releaseAllKeys();
    } else if (trickClock.getElapsedTime().asMicroseconds() % MAX_MILLISECONDS_FOR_FLIP
            < MAX_MILLISECONDS_FOR_FLIP) {
        scoreHundred = false;
        keyboard.releaseAllKeys();
    }
}

void CartSurferEngine::spinMinecart() {
    const int MAX_MILLISECONDS_FOR_SPIN = 1100;
    const int MAX_MINECART_JUMP_TIME = 600;
    const int MAX_MINECART_SPIN_TIME = 650;
    if (!isCartDown && trickClock.getElapsedTime().asMilliseconds() % MAX_MILLISECONDS_FOR_SPIN
            < MAX_MINECART_JUMP_TIME) {
        keyboard.pressKey("Space");
    } else if (trickClock.getElapsedTime().asMilliseconds() % MAX_MILLISECONDS_FOR_SPIN
            < MAX_MINECART_SPIN_TIME) {
        keyboard.pressKey("Right");
        keyboard.releaseAllKeys();
    } else if (trickClock.getElapsedTime().asMicroseconds() % MAX_MILLISECONDS_FOR_SPIN 
            < MAX_MILLISECONDS_FOR_SPIN) {
        scoreHundred = true;
        keyboard.releaseAllKeys();
    }
}