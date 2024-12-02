#include <SFML/Graphics.hpp>
#include <iostream>

sf::Texture spritesheet;  // Texture to hold the sprite sheet
sf::Sprite invader;       // Sprite to display the invader

sf::RenderWindow window(sf::VideoMode(800, 600), "Spritesheet Example");  // Create a window

// Function to load the sprite sheet and set the texture rectangle for the invader
void Load() {
    // Attempt to load the texture from a file
    if (!spritesheet.loadFromFile("C:/Users/Cmerc/Games_Games/Games_New/res/img/invaders_sheet.png")) {
        std::cerr << "Failed to load spritesheet!" << std::endl;
    }
    // Set the texture for the invader sprite
    invader.setTexture(spritesheet);

    // Set the portion of the sprite sheet to display (top-left 32x32 square in this case)
    invader.setTextureRect(sf::IntRect(0, 0, 32, 32));  // Select the first frame of the sprite sheet

    // Set the initial position of the invader on the screen
    invader.setPosition(0.f, 0.f);  // Set to position (100, 100)
}

// Function to render the sprite on the window
void Render() {
    window.clear();  // Clear the window before drawing anything
    window.draw(invader);  // Draw the invader sprite
    window.display();  // Display the updated window contents
}

int main() {
    Load();  // Load the sprite sheet and set up the invader

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();  // Close the window if the user presses the close button
            }
        }

        Render();  // Render the invader sprite
    }

    return 0;
}
