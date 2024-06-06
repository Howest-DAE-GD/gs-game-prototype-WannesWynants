#include "pch.h"
#include "Game.h"
#include "utils.h"
#include "SVGFiles.h"
#include "iostream"

Game::Game( const Window& window ) 
	:BaseGame{ window }
{
	Initialize();
}

Game::~Game( )
{
	Cleanup( );
}

void Game::GetCollisionGround(const std::vector<std::vector<Point2f>>& vertices)
{
	Point2f m_P3{ m_PosBall.x, m_PosBall.y };
	Point2f m_P1{ m_PosBall.x, m_PosBall.y - 7.f };
	Point2f m_P4{ m_PosBall.x + 7.f ,m_PosBall.y };
	Point2f m_P2{ m_PosBall.x - 7.f ,m_PosBall.y };

	utils::HitInfo result;

	for (int idx{ 0 }; idx < vertices.size(); ++idx)
	{
		if (utils::Raycast(vertices[idx], m_P3, m_P1, result))
		{
			m_Velocity.y = 0;
			m_PosBall.y = result.intersectPoint.y + 7.1f;
		}
		if (utils::Raycast(vertices[idx], m_P3, m_P4, result))
		{
			m_PosBall.x = result.intersectPoint.x - 7.1f;
		}
		if (utils::Raycast(vertices[idx], m_P3, m_P2, result))
		{
			m_PosBall.x = result.intersectPoint.x + 7.1f;
		}
	}
}

void Game::Initialize( )
{
	m_pMap = new Texture{ "Map2.png" };
	m_pMain = new SVGFiles();
	m_PosBall.x = GetViewPort().left + 30.f;
	m_PosBall.y = GetViewPort().height - 30.f;
	
}

void Game::Cleanup( )
{
	delete m_pMap;
	m_pMap = nullptr;
}

void Game::Update( float elapsedSec)
{
	GetCollisionGround(m_pMain->GetVertices());  

	float speed{ 200.f * elapsedSec };
	const float gravity{ -9.81f };
	m_Velocity.y += gravity;
	m_PosBall.y += m_Velocity.y * elapsedSec;

}

void Game::Draw( ) const
{
	ClearBackground( );

	
	glPushMatrix();
	{
		if (m_Rotation == RotationState::d90)
		{
			glTranslatef(533, 0, 0);
			glRotatef(90, 0, 0, 1);
			
			m_pMap->Draw();
		}
		else if (m_Rotation == RotationState::d180)
		{
			glTranslatef(533, 534, 0);
			glRotatef(180, 0, 0, 1);
			
			m_pMap->Draw();
		}
		else if (m_Rotation == RotationState::d270)
		{
			glTranslatef(0, 534, 0);
			glRotatef(270, 0, 0, 1);
			
			m_pMap->Draw();
		}
		
		m_pMap->Draw();

	}
	glPopMatrix();

	utils::SetColor(Color4f(1.f, 0.f, 0.f, 1.f));

	utils::FillEllipse(m_PosBall.x, m_PosBall.y, 7.f, 7.f);
	utils::SetColor(Color4f(0.f, 0.f, 0.f, 1.f));
	m_pMain->Draw();
	
	
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	
	switch ( e.keysym.sym )
	{
	case SDLK_a:
		--m_PosBall.x;
		break;
	case SDLK_d:
		++m_PosBall.x;
		break;
	}
}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
	switch (e.keysym.sym)
	{
	case SDLK_LEFT:
		std::cout << "Left arrow key released\n";
		if (m_Rotation == RotationState::d0)
		{
			m_Rotation = RotationState::d90;
			m_TempPosBallY = m_PosBall.y;
			m_TempPosBallX = m_PosBall.x;

			m_PosBall.y = m_PosBall.x;

			m_PosBall.x = 534.f - m_TempPosBallY;
			

		}
		else if (m_Rotation == RotationState::d90)
		{
			m_Rotation = RotationState::d180;
			m_TempPosBallY = m_PosBall.y;
			m_TempPosBallX = m_PosBall.x;

			m_PosBall.y = m_PosBall.x;

			m_PosBall.x = 534.f - m_TempPosBallY;
			
		}
		else if (m_Rotation == RotationState::d180)
		{
			m_Rotation = RotationState::d270;
			m_TempPosBallY = m_PosBall.y;
			m_TempPosBallX = m_PosBall.x;

			m_PosBall.y = m_PosBall.x;

			m_PosBall.x = 534.f - m_TempPosBallY;
		}
		else if (m_Rotation == RotationState::d270)
		{
			m_Rotation = RotationState::d0;
			m_TempPosBallY = m_PosBall.y;
			m_TempPosBallX = m_PosBall.x;

			m_PosBall.y = m_PosBall.x;

			m_PosBall.x = 534.f - m_TempPosBallY;

		}
		m_pMain->TransformPointsLeft();
		std::cout << m_PosBall.x << " , " << m_PosBall.y << "\n";
		break;
	
	case SDLK_RIGHT:
		std::cout << "Right arrow key released\n";
		if (m_Rotation == RotationState::d0)
		{
			m_Rotation = RotationState::d270;
			m_TempPosBallX = m_PosBall.x;
			m_TempPosBallY = m_PosBall.y;

			m_DistanceTemp = 533.f - m_PosBall.x;
			m_PosBall.y = m_DistanceTemp;

			m_PosBall.x = m_TempPosBallY; 

		}
		else if (m_Rotation == RotationState::d90)
		{
			m_Rotation = RotationState::d0;
			m_TempPosBallX = m_PosBall.x;
			m_TempPosBallY = m_PosBall.y;

			m_DistanceTemp = 533.f - m_PosBall.x;
			m_PosBall.y = m_DistanceTemp;

			m_PosBall.x = m_TempPosBallY;

		}
		else if (m_Rotation == RotationState::d180)
		{
			m_Rotation = RotationState::d90;
			m_TempPosBallX = m_PosBall.x;
			m_TempPosBallY = m_PosBall.y;

			m_DistanceTemp = 533.f - m_PosBall.x;
			m_PosBall.y = m_DistanceTemp;

			m_PosBall.x = m_TempPosBallY;

		}
		else if (m_Rotation == RotationState::d270)
		{
			m_Rotation = RotationState::d180;
			m_TempPosBallX = m_PosBall.x;
			m_TempPosBallY = m_PosBall.y;

			m_DistanceTemp = 533.f - m_PosBall.x;
			m_PosBall.y = m_DistanceTemp;

			m_PosBall.x = m_TempPosBallY;
		}
		m_pMain->TransformpointsRight();
		std::cout << m_PosBall.x << " , " << m_PosBall.y << "\n";
		break;
	}

	

	

}

void Game::ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e )
{
	//std::cout << "MOUSEMOTION event: " << e.x << ", " << e.y << std::endl;
}

void Game::ProcessMouseDownEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONDOWN event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
	
}

void Game::ProcessMouseUpEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONUP event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
}

void Game::ClearBackground( ) const
{
	glClearColor( 0.2f, 0.2f, 0.2f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}
