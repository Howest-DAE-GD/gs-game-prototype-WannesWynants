#pragma once
#include "BaseGame.h"
#include "Texture.h"
#include "vector"
#include "Vector2f.h"

class SVGFiles;
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

	
	Texture* m_pMap;
	SVGFiles* m_pMain;
	Point2f m_PosBall;
	float m_TempPosBallX, m_TempPosBallY,m_DistanceTemp,m_Distance;
	Vector2f m_Velocity;
	bool m_IsLeft;
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