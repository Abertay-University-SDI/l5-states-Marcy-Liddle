#pragma once
#include "Framework/GameObject.h"
class Player :
    public GameObject
{
public:
    Player();

    void handleInput(float dt) override;
    void update(float dt) override;
    void collisionResponse(GameObject& collider) override;
private:
    sf::Texture m_texture;
    sf::Vector2f m_acceleration;
    bool m_isOnGround = false;
    sf::Vector2f m_oldPosition;

    const float GRAVITY = 10.f;
    const float SPEED = 10.f;
    const float JUMP_FORCE = 5.0f;
    const float COEFF_RESTITUTION = 0.9f;
};

