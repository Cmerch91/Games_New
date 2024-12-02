// ship.h
#pragma once
#include <SFML/Graphics.hpp>

class Ship : public sf::Sprite {
public:
    Ship(const sf::Texture& texture, const sf::Vector2f& position);
    void Update(float dt);
    void MoveLeft();
    void MoveRight();

private:
    float speed; // Player speed
};

// ship.cpp
#include "ship.h"

Ship::Ship(const sf::Texture& texture, const sf::Vector2f& position)
    : sf::Sprite(texture) {
    this->setPosition(position);
    speed = 200.f; // Set speed
}

void Ship::Update(float dt) {
    // Update movement for the ship
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        MoveLeft();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        MoveRight();
    }
}

void Ship::MoveLeft() {
    this->move(-speed * 0.016f, 0);  // Move left
}

void Ship::MoveRight() {
    this->move(speed * 0.016f, 0);  // Move right
}
