#include <SFML/Graphics.hpp>
#include "ship.h"
#include "game.h"
#include "bullet.h"  // Include the Bullet class
#include <iostream>
#include <vector>

// Define ships and bullets vectors here
std::vector<Ship*> ships;
std::vector<Bullet*> playerBullets;  // Store player bullets
std::vector<Bullet*> enemyBullets;   // Store enemy bullets
bool groupDirectionRight = true;  // Initially moving to the right

float lastShotTime = 0.f;  // Time since the last shot
float shootCooldown = 0.5f; // Half second cooldown for shooting

// Function to check collision between bullets and invaders (example)
void checkBulletCollisions() {
    for (auto bullet : playerBullets) {
        for (auto ship : ships) {
            if (bullet->getGlobalBounds().intersects(ship->getGlobalBounds())) {
                // Bullet hits the ship
                delete bullet;  // Remove bullet
                delete ship;    // Remove the ship (invader)
                break;  // Exit inner loop once the bullet collides with something
            }
        }
    }
}

int main() {
    // SFML window setup
    sf::RenderWindow window(sf::VideoMode(gameWidth, gameHeight), "Space Invaders");

    // Load texture for invader
    sf::Texture invaderTexture;
    if (!invaderTexture.loadFromFile("C:/Users/Cmerc/Games_Games/Games_New/res/img/invaders_sheet.png")) {
        std::cerr << "Error loading invader texture!" << std::endl;
        return -1;
    }

    // Load the player ship from the invader sheet (7th sprite in the top row)
    sf::Texture playerTexture;
    sf::IntRect playerShipRect(192, 0, 32, 32);  // 7th sprite, 32x32 (adjusted for 7th sprite)

    // Create player ship (initial position)
    Ship* playerShip = new Ship(invaderTexture, playerShipRect, sf::Vector2f(400.f, 500.f));  // Adjusted to start at bottom

    // Create invaders and add them to the ships vector
    for (int r = 0; r < invaders_rows; ++r) {
        auto rect = sf::IntRect(0, 0, 32, 32);  // Set the texture rectangle (example values)
        for (int c = 0; c < invaders_columns; ++c) {
            // Set the position with reduced spacing to make them closer together
            sf::Vector2f position(30.f + 30.f * c, 30.f + 30.f * r);  // Adjusted spacing and start position

            Invader* inv = new Invader(invaderTexture, rect, position);  // Pass all three arguments
            ships.push_back(inv);  // Add the new invader to the ships vector
        }
    }

    // Game loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Update shooting cooldown
        lastShotTime += 1.0f / 60.0f;

        // Player shooting logic (firing bullets)
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && lastShotTime >= shootCooldown) {
            playerBullets.push_back(new Bullet(sf::Vector2f(playerShip->getPosition().x + 16.f, playerShip->getPosition().y), false));  // Adjusted position
            lastShotTime = 0.f;  // Reset cooldown
        }

        // Update player ship and bullets
        float dt = 1.0f / 60.0f;  // Delta time (fixed at 60 FPS for simplicity)
        playerShip->Update(dt);  // Update the player ship
        for (auto bullet : playerBullets) {
            bullet->Update(dt);  // Update the player's bullets
        }

        // Update the ships (invaders)
        for (auto& ship : ships) {
            ship->Update(dt);  // Update the invader ship movement
        }

        // Check for collisions between player bullets and invaders
        checkBulletCollisions();

        // Render everything (ships and bullets)
        window.clear();
        window.draw(*playerShip);  // Draw the player ship
        for (auto& ship : ships) {
            window.draw(*ship);  // Draw each invader
        }
        for (auto& bullet : playerBullets) {
            window.draw(*bullet);  // Draw each player bullet
        }

        window.display();
    }

    // Cleanup
    delete playerShip;  // Clean up the player ship
    for (auto& ship : ships) {
        delete ship;  // Clean up invaders (ships)
    }
    for (auto& bullet : playerBullets) {
        delete bullet;  // Clean up player bullets
    }

    return 0;
}
