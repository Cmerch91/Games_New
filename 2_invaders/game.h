#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "ship.h"

// Game dimensions
constexpr uint16_t gameWidth = 800;
constexpr uint16_t gameHeight = 600;

// Invader grid dimensions
constexpr uint16_t invaders_rows = 8;
constexpr uint16_t invaders_columns = 25;

// External variables
extern sf::Texture spritesheet;
extern std::vector<Ship*> ships;  // Declare ships here

// Add a flag for group direction control in the game.h or ship.h if needed.
extern bool groupDirectionRight;  // Flag for group direction
