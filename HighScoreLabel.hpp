#pragma once
#include <functional>
#include "GenericLabel.hpp"

// typedef std::function<void()> buttonAction;
class HighScoreLabel : public GenericLabel {

private:
    static std::string document;
    sf::Text text;
    sf::Font& font;
    sf::RenderWindow window;
public:
    HighScoreLabel(std::string identifier, sf::Vector2f position, sf::Font& font, sf::Color textColor, sf::RenderWindow& window, std::string doc);
    ~HighScoreLabel();

    void update() override;
    void render(sf::RenderWindow& window) override;

    static std::string GetHighScores(int highScoreAmount);

    static void SetHighScores(int highScoreAmount, int currentScore);
};
