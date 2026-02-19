#pragma once
#include "Framework/GameObject.h"
class Switch :
    public GameObject
{
public:
    void toggle();
private:
    bool m_isOn;
    sf::IntRect m_rightRect = { {6 * 19,3 * 19}, {18,18} };
    sf::IntRect m_leftRect = { {4 * 19,3 * 19}, {18,18} };
};



