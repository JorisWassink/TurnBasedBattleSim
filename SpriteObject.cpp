#include "SpriteObject.hpp"

#include "GenericLabel.hpp"

SpriteObject::SpriteObject(std::string identifier, sf::Sprite spr) : GameObject(identifier) {
    sprite = spr;
}

SpriteObject::~SpriteObject() { }


void SpriteObject::render(sf::RenderWindow& window) {
    window.draw(sprite);
}
void SpriteObject::update() {}
