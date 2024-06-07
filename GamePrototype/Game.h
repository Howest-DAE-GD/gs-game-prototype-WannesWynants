#pragma once
#include "BaseGame.h"
#include "Texture.h"
#include "vector"
#include "Vector2f.h"

class SVGFiles;
class People;
class Game : public BaseGame
{
public:
	explicit Game( const Window& window );
	Game(const Game& other) = delete;
	Game& operator=(const Game& other) = delete;
	Game( Game&& other) = delete;
	Game& operator=(Game&& other) = delete;
	// http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rh-override
	~Game();

	void Update( float elapsedSec ) override;
	void Draw( ) const override;

	// Event handling
	void ProcessKeyDownEvent( const SDL_KeyboardEvent& e ) override;
	void ProcessKeyUpEvent( const SDL_KeyboardEvent& e ) override;
	void ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e ) override;
	void ProcessMouseDownEvent( const SDL_MouseButtonEvent& e ) override;
	void ProcessMouseUpEvent( const SDL_MouseButtonEvent& e ) override;

private:
	std::vector<People*> m_People;
	
	int m_Timer;
	float m_TimerFloat;
	Texture* m_pTimer;
	Texture* m_pTimeUp;
	bool m_IsTimeUp;
	Texture* m_pMap;
	SVGFiles* m_pMain;
	Point2f m_PosBall;
	float m_TempPosBallX, m_TempPosBallY,m_DistanceTemp,m_Distance;
	Vector2f m_Velocity;
	bool m_IsLeft;
	Rectf m_Exit, m_ExitBottom, m_ExitRight, m_ExitTop, m_ExitLeft;
	Rectf m_TempExit;
	Texture* m_pEscaped;
	Texture* m_pScore;
	bool m_IsEscaped;
	bool m_IsA, m_IsD;
	int m_CollectedPeople;

	//bool rotation;
	
	enum class RotationState {
		d0,
		d90,
		d180,
		d270
	};
	RotationState m_Rotation{ RotationState::d0 };
	
	void GetCollisionGround(const std::vector<std::vector<Point2f>>& vertices);
	void Initialize();
	void Cleanup( );
	void ClearBackground( ) const;
};