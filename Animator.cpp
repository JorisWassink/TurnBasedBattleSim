#include "Animator.hpp"

#include "Character.hpp"

Animator::Animator(){}

void Animator::setBody(sf::Sprite& bod) {
    body = &bod;
}



bool Animator::Backflip(float speed) {
    body->setRotation(body->getRotation() + speed);
    //printf("spinnin %f\n", body->getRotation());

    if (body->getRotation() > 350) {
        body->setRotation(0);
        return true;
    }

    return false;
}


bool front = false;


bool Animator::HeadButt(float speed) {
    constexpr float maxRotation = 45.0f;
    constexpr float resetThreshold = 5.0f;

    //printf("lets see, the current rotation is currently %f\n", body->getRotation());

    body->rotate(front ? -speed : speed);

    if (body->getRotation() > maxRotation) {
        front = true;
    } else if (front && body->getRotation() < resetThreshold) {
        body->setRotation(0);
        front = false;
        return true;
    }
    return false;
}

