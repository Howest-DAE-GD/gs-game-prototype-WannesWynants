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

	// FUNCTIONS
	/*Point2f p1{ Point2f(0,720 )}, p2{ Point2f(60,720) }, p3{ Point2f(420,720) }, p4{ Point2f(600,720) }, p5{ Point2f(780,720) },
	p6{ Point2f(180, 660) }, p7{ Point2f(300,660) }, p8{ Point2f(480,660) }, p9{ Point2f(720,660) }
	, p10{ Point2f(60,600) }, p11{ Point2f(180,600) }, p12{ Point2f(240,600) }, p13{ Point2f(420,600) }, p14{ Point2f(480,600) }, p15{ Point2f(540,600) }, p16{ Point2f(600,600) }, p17{ Point2f(660,600) }
	, p18{ Point2f(0,540) }, p19{ Point2f(60,540) }, p20{ Point2f(660,540) }, p21{ Point2f(720,540) }
	, p22{ Point2f(300,480) }, p23{ Point2f(360,480) }, p24{ Point2f(420,480) }, p25{ Point2f(600,480) }, p26{ Point2f(660,480) }, p27{ Point2f(720,480) }
	, p28{ Point2f(60,420) }, p29{ Point2f(240,420) }, p29b{ Point2f(360,420) }, p30{ Point2f(420,420) }, p31{ Point2f(720,420) }, p32{ Point2f(780,420) }
	, p33{ Point2f(60,360) }, p34{ Point2f(180,360) }, p35{ Point2f(300,360) }, p36{ Point2f(540,360) }, p37{ Point2f(660,360) }, p38{ Point2f(720,360) }
	, p39{ Point2f(120,300) }, p40{ Point2f(300,300) }, p41{ Point2f(600,300) }
	, p42{ Point2f(180,240) }, p43{ Point2f(540,240) }, p44{ Point2f(660,240) }, p45{ Point2f(720,240) }, p46{ Point2f(780,240) }
	, p47{ Point2f(0,180) }, p48{ Point2f(60,180) }
	, p49{ Point2f(180,120) }, p50{ Point2f(480,120) }, p51{ Point2f(660,120) }
	, p52{ Point2f(60,60) }, p53{ Point2f(120,60) }, p54{ Point2f(180,60) }, p55{ Point2f(480,60) }, p56{ Point2f(540,60) }, p57{ Point2f(660,60) }
	, p58{ Point2f(0,0) }, p59{ Point2f(480,0) }, p60{ Point2f(660,0) }, p61{ Point2f(780,0) };*/
	Texture* m_pMap;
	SVGFiles* m_pMain;
	Point2f m_PosBall;
	float m_TempPosBallX, m_TempPosBallY,m_DistanceTemp,m_Distance;
	Vector2f m_Velocity;
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