#include "pch.h"
#include "People.h"
#include "utils.h"

People::People(const Point2f& pos)
	:m_PosPeople{pos},
	m_Radius{7.f},
	m_IsPickedUp{false},
	m_Color{Color4f(1,0.7f,0,1)}
{
}

void People::Draw()const
{
	if (!m_IsPickedUp)
	{
		utils::SetColor(m_Color);
		utils::FillEllipse(m_PosPeople, m_Radius, m_Radius);
	}
}

bool People::CollectPerson(const Circlef& hitbox)
{
	if (utils::IsOverlapping(hitbox, GetHitbox()))
	{
		m_IsPickedUp = true;
		return true;
	}
	else return false;
}

Circlef People::GetHitbox()const
{
	return Circlef{ m_PosPeople, m_Radius };
}

void People::rotateCoins90Degrees(float screenWidth, float screenHeight) {
    float centerX = screenWidth / 2.0f;
    float centerY = screenHeight / 2.0f;

    float tempX = m_PosPeople.x - centerX;
    float tempY = m_PosPeople.y - centerY;

    float rotatedX = -tempY;
    float rotatedY = tempX;

    m_PosPeople.x = rotatedX + centerX;
    m_PosPeople.y = rotatedY + centerY;
}

void People::rotateCoinsNeg90Degrees(float screenWidth, float screenHeight)
{
    float centerX = screenWidth / 2.0f;
    float centerY = screenHeight / 2.0f;

    float tempX = m_PosPeople.x - centerX;
    float tempY = m_PosPeople.y - centerY;

    float rotatedX = tempY;
    float rotatedY = -tempX;

    m_PosPeople.x = rotatedX + centerX;
    m_PosPeople.y = rotatedY + centerY;
}

bool People::IsPickedUp()
{
    return m_IsPickedUp;
}

