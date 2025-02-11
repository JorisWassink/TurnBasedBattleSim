#include "gameObject.hpp"

GameObject::GameObject() { }

GameObject::GameObject(std::string identifier) : identifier(identifier) { }

GameObject::GameObject(const GameObject& other) : identifier(other.getIdentifier()) { }

GameObject::~GameObject() { }

void GameObject::AddChild(GameObject& child) {

    this->children.push_back(&child);
}

void GameObject::handleEvent(const sf::Event& event, sf::RenderWindow& window) {}

void GameObject::DeleteChild(std::string id) {
    int size = children.size();
    for (int i = 0; i < size; i++)
    {
        if (children[i]->identifier == id) { children[i]->Delete(); }
    }
}

void GameObject::Delete() {
    delete this;
}

std::string GameObject::getIdentifier() const {
    return this->identifier;
}