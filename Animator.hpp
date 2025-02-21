#pragma once
#include <SFML/Graphics.hpp>

// Forward declaration of the Character class
class Character;

class Animator {
public:
    Animator();
    void setBody(sf::Sprite& bod);
    bool Backflip(float speed);

private:
    sf::Sprite* body;
};
