#pragma once
#include <SFML/Graphics.hpp>

class Bullet : public sf::Sprite {
public:
    // Constructor: takes position and mode (false for player, true for enemy)
    Bullet(const sf::Vector2f& pos, const bool mode);

    // Destructor
    ~Bullet() = default;

    // Update method to move the bullet
    void Update(const float& dt);

    // Static function to initialize bullets (optional, if needed)
    static void Initialize();

protected:
    // Default constructor (not used directly)
    Bullet();

    bool _mode;  // false=player bullet, true=Enemy bullet
};
