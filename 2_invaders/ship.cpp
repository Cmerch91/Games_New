#include "ship.h"
#include "game.h"
#include <SFML/Graphics.hpp>
#include <iostream>

// Default constructor for Ship (hidden from use)
Ship::Ship() {}

// Constructor for Ship
Ship::Ship(sf::Texture& texture, sf::IntRect ir) : _sprite(ir) {
    setTexture(texture);
    setTextureRect(_sprite);
}

// Pure virtual destructor for Ship
Ship::~Ship() = default;

// Update function for Ship
void Ship::Update(const float& dt) {}

// Default constructor for Invader
Invader::Invader() : Ship(), direction(true), speed(50.f) {}

// Constructor for Invader
Invader::Invader(sf::Texture& texture, sf::IntRect ir, sf::Vector2f pos)
    : Ship(texture, ir), direction(true), speed(1.f) {  // Adjust speed (e.g., 50.f for slower movement)
    setOrigin(sf::Vector2f(16.f, 16.f)); // Set origin
    setPosition(pos); // Set position
}


void Invader::Update(const float& dt) {
    // Scale the speed according to delta time
    float speed = 1.f;  // You can adjust this value to be faster or slower as needed
    float moveDistance = speed * dt;  // This ensures movement is frame rate independent

    // Move invaders as a group based on the direction
    if (groupDirectionRight) {
        move(sf::Vector2f(moveDistance, 0.f));  // Move right
    }
    else {
        move(sf::Vector2f(-moveDistance, 0.f));  // Move left
    }

    // Check if the first invader (in the topmost row) has hit the edge of the screen
    if (getPosition().x > gameWidth - 32 && groupDirectionRight) {
        // When the first invader hits the right wall, reverse the direction of the entire group
        groupDirectionRight = false;
    }
    if (getPosition().x < 0 && !groupDirectionRight) {
        // When the first invader hits the left wall, reverse the direction of the entire group
        groupDirectionRight = true;
    }
}
