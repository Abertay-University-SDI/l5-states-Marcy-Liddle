#include "Switch.h"

// swaps Switch isOn state and sets Texturerect appropriately.
void Switch::toggle()
{
    m_isOn = !m_isOn;
    if (m_isOn) setTextureRect(m_leftRect);
    else setTextureRect(m_rightRect);
}