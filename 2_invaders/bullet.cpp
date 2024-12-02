#include "bullet.h"
#include "game.h"
#include <iostream>
using namespace sf;
using namespace std;

// Constructor to initialize the bullet's position and mode
Bullet::Bullet(const sf::Vector2f& pos, const bool mode) : _mode(mode) {
    // Set the sprite's position and texture
    setPosition(pos);

    // Load different textures based on the mode (Player vs Enemy)
    sf::Texture texture;
    if (!_mode) {
        if (!texture.loadFromFile("player_bullet.png")) {
            // Handle error
            std::cerr << "Error loading player bullet texture!" << std::endl;
        }
    }
    else {
        if (!texture.loadFromFile("enemy_bullet.png")) {
            // Handle error
            std::cerr << "Error loading enemy bullet texture!" << std::endl;
        }
    }
    setTexture(texture);
}

// Update the bullet's position based on its mode (up or down)
void Bullet::Update(const float& dt) {
    move(Vector2f(0, dt * 200.0f * (_mode ? 1.0f : -1.0f)));  // Move based on the direction
}
