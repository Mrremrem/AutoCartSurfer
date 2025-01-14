#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include "CartSurferEngine.h"
#include <fstream>
#include <stdexcept>
#include <unordered_map>

/*
 * Loads config and sets values in map
 * Pre: None
 * Post: None
 */
std::unordered_map<std::string , sf::Vector2i> loadConfig(const std::string& configDir) {
    std::unordered_map<std::string, sf::Vector2i> configMap;

    std::ifstream configFile;
    configFile.open(configDir);

    if (!configFile.is_open()) {
        throw std::runtime_error("Unable to open config.txt");
    }

    while (configFile.good()) {
        std::string type;
        configFile >> type;

        const std::string COMMENT = "#";

        if (type == COMMENT) {
            std::string storeComment;
            std::getline(configFile, storeComment);
        } else {
            // Stores either arrow pos or blue coin screen pos
            sf::Vector2i pos;
            configFile >> pos.x >> pos.y;

            configMap[type] = pos;
        }
    }

    return configMap;
}


int main() {
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Auto CartSurfer");
    window.setFramerateLimit(60);

    const std::string LEFT_ARROW_KEY = "LEFT_ARROW_POS";
    const std::string RIGHT_ARROW_KEY = "RIGHT_ARROW_POS";
    const std::string COINS_EARNED_SCREEN_KEY = "COINS_EARNED_SCREEN_POS";
    const std::string CONFIG_DIR = "config.txt";

    std::unordered_map<std::string, sf::Vector2i> configMap = loadConfig(CONFIG_DIR);
    CartSurferEngine engine(configMap[LEFT_ARROW_KEY], configMap[RIGHT_ARROW_KEY],
                configMap[COINS_EARNED_SCREEN_KEY]);
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
