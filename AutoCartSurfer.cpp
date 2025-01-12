#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include "CartSurferEngine.h"


int main() {
    sf::RenderWindow window(sf::VideoMode(1920, 1200), "Auto CartSurfer");
    window.setFramerateLimit(60);

    CartSurferEngine engine;
    while (window.isOpen() && engine.isRunning()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        engine.run();

        window.clear(sf::Color::Magenta);
        window.display();
    }

}
