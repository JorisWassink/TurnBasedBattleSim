#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

class GameObject {
private:
    const std::string identifier;
    std::vector<GameObject*> children;
public:
    GameObject();
    GameObject(std::string identifier);
    GameObject(const GameObject& other);
    virtual ~GameObject();
public:
    virtual void AddChild(GameObject& child);
    virtual void DeleteChild(std::string identifyer);
    virtual void Delete();
    virtual void update() = 0;
    virtual void render(sf::RenderWindow& window) = 0;
    virtual void handleEvent(const sf::Event& event, sf::RenderWindow& window);
    std::string getIdentifier() const;
};