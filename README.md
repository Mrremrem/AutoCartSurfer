# AutoCartSurfer - Automate Cart Surfer gameplay from Club Penguin with ease !!!

![Minecart Snoo](Minecart%20Snoo.png)

AutoCartSurfer is a cross-platform automation tool for the [Cart Surfer mini-game](https://clubpenguin.fandom.com/wiki/Cart_Surfer) from [Club Penguin](https://en.wikipedia.org/wiki/Club_Penguin), tested and verified to work with Club Penguin Journey (CPJ) and Club Penguin Legacy (CPL). Whether you're aiming to rack up coins or perfect your moves, this tool simplifies gameplay with efficient and customizable actions.

# Features
- Cross-Platform Compatibility: Works seamlessly on Windows and Linux.
- Automated Moves: Perform flips, spins, and drifts effortlessly with intelligent input handling.
- Dynamic Color Detection: Detects on-screen prompts (arrows, coins earned screen) using pixel color recognition.
- Customizable: Built-in support for flexible delays, input methods, and game variations.
- Lightweight & Fast: Designed with performance in mind, utilizing SFML for speed and reliability.

# How It Works
AutoCartSurfer uses pixel-based color detection to interpret the game's visual cues (e.g., arrows or screen changes) and sends automated key inputs accordingly. The program adjusts its actions dynamically to ensure smooth and accurate gameplay.

The supported moves include:
- Drift: Automatically follows directional arrows (left or right).
- Flip: Flips the cart to score points.
- Spin: Spins the cart based on timing cues.

# Requirements
### For Windows
- [SFML 2.5.1](https://www.sfml-dev.org/) or later (Download here)
- [MinGW-w64](https://en.wikipedia.org/wiki/MinGW) or [Visual Studio](https://en.wikipedia.org/wiki/Visual_Studio)
- Windows 10 or later

### For Linux
- [SFML 2.5.1](https://www.sfml-dev.org/) or later (install via your package manager, e.g., sudo apt install libsfml-dev or sudo pacman -S sfml for Arch users)
- X11 libraries (libxtst-dev, etc.)
- [Linux distribution with X11](https://en.wikipedia.org/wiki/X_Window_System) ([Wayland](https://en.wikipedia.org/wiki/Wayland_(protocol)) is not supported yet unfortunately)
