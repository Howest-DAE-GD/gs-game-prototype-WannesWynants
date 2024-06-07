#pragma once
class People
{
public:
    People(const Point2f& pos);
    void Draw() const;
    bool CollectPerson(const Circlef& hitbox);
    void rotateCoins90Degrees(float screenWidth, float screenHeight);
    void rotateCoinsNeg90Degrees(float screenWidth, float screenHeight);
    bool IsPickedUp();
private:
    Point2f m_PosPeople;
    float m_Radius;
    bool m_IsPickedUp;
    Color4f m_Color;
    Circlef GetHitbox() const;

};

