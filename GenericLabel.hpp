#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.hpp"


class GenericLabel : public GameObject {
private:
	sf::Font font;
	sf::Text text;
	

public:
	std::string textStr;
	sf::Vector2f lPosition;
	GenericLabel(const std::string &textS = "", sf::Vector2f position = sf::Vector2f(0,0));
	~GenericLabel();
public:
	void render(sf::RenderWindow& Window) override;
	void update() override;
	void SetString(const std::string &textS = "");
};