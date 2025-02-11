#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.hpp"


class SpriteObject : public GameObject {
private:
    sf::Sprite sprite;


public:

    SpriteObject(std::string identifier, sf::Sprite spr);
    ~SpriteObject();
public:
    void render(sf::RenderWindow& Window) override;
    void update() override;
};