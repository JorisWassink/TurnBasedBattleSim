#include "Animator.hpp"

#include "Character.hpp"

Animator::Animator(){}

void Animator::setBody(sf::Sprite& bod) {
    body = &bod;
}



bool Animator::Backflip(float speed) {
    body->setRotation(body->getRotation() + speed);
    printf("spinnin %f\n", body->getRotation());

    if (body->getRotation() > 350) {
        body->setRotation(0);
        return true;
    }

    return false;
}
