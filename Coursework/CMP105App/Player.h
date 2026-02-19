#pragma once
#include "Framework/GameObject.h"
#include "Switch.h"

class Player :
    public GameObject
{
public:
    Player();

    void handleInput(float dt) override;
    void update(float dt) override;
    void collisionResponse(GameObject& collider) override;

    void setSwitch(Switch* switchy)
    {
        m_switch = switchy;
    }
    void setFlag(GameObject* mcFlag)
    {
        m_flag = mcFlag;
    }

    bool endGame() { return m_wantsToEndGame; }
    void setGameEnd(bool yesOrNo) { m_wantsToEndGame = yesOrNo; }

private:
    sf::Texture m_texture;
    sf::Vector2f m_acceleration;
    bool m_isOnGround = false;
    sf::Vector2f m_oldPosition;

    Switch * m_switch;
    GameObject* m_flag;

    bool m_wantsToEndGame = false;
 
    const float GRAVITY = 10.f;
    const float SPEED = 10.f;
    const float JUMP_FORCE = 5.0f;
    const float COEFF_RESTITUTION = 0.9f;
};

