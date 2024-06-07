#include "pch.h"
#include "Game.h"
#include "utils.h"
#include "SVGFiles.h"
#include "iostream"
#include "People.h"

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
	m_Exit = Rectf(230, 5, 20, 30);
	m_ExitBottom = Rectf(230, 5, 20, 30);
	m_ExitRight = Rectf(498, 230, 30, 20);
	m_ExitTop = Rectf(280, 498, 20, 30);
	m_ExitLeft = Rectf(5, 280, 30, 20);
	m_pEscaped = new Texture("You Escaped", "You escaped.otf", 50.f, Color4f{1,0,0,1} ); 
	m_pScore = new Texture("Score: 0", "You escaped.otf", 25.f, Color4f{1,0,0,1});
	m_IsEscaped = false;
	m_IsA = false;
	m_IsD = false;
	m_People.push_back(new People{ Point2f(90,475) });
	m_People.push_back(new People{ Point2f(260,440) });
	m_People.push_back(new People{ Point2f(25,180) });
	m_People.push_back(new People{ Point2f(244,255) });
	m_People.push_back(new People{ Point2f(160,65) });
	m_People.push_back(new People{ Point2f(420,370) });
	m_CollectedPeople = 0;
	m_Timer = 80;
	m_TimerFloat = 0.f;
	m_IsTimeUp = false;
	m_pTimer = new Texture("Time: 80", "You escaped.otf", 25.f, Color4f{ 1,0,0,1 });
	m_pTimeUp = new Texture("Time Up!", "You escaped.otf", 50.f, Color4f{ 1,0,0,1 });
}

void Game::Cleanup( )
{
	delete m_pMap;
	m_pMap = nullptr;
}

void Game::Update( float elapsedSec)
{
	GetCollisionGround(m_pMain->GetVertices());  

	float speed{ 50.f * elapsedSec };
	const float gravity{ -9.81f };
	m_Velocity.y += gravity;
	m_PosBall.y += m_Velocity.y * elapsedSec;

	Circlef ball{ m_PosBall.x, m_PosBall.y, 7.f};
	
	m_TimerFloat += elapsedSec;
	if (m_TimerFloat >= 1.f && !m_IsTimeUp && !m_IsEscaped)
	{
		--m_Timer;
		delete m_pTimer;
		m_pTimer = nullptr;
		m_pTimer = new Texture("Time: " + std::to_string(m_Timer), "You escaped.otf", 25.f, Color4f{1,0,0,1});
		m_TimerFloat = 0.f;
	}
	if (m_Timer <= 0 && !m_IsTimeUp && !m_IsEscaped)
	{
		m_IsTimeUp = true;
		
	}

	if (m_Rotation == RotationState::d90)
	{
		if (utils::IsOverlapping(m_ExitRight,ball) && !m_IsEscaped)
		{
			m_IsEscaped = true;

		}
	}
	else if (m_Rotation == RotationState::d180)
	{
		if (utils::IsOverlapping(m_ExitTop, ball) && !m_IsEscaped)
		{
			m_IsEscaped = true;

		}
	}
	else if (m_Rotation == RotationState::d270)
	{
		if (utils::IsOverlapping(m_ExitLeft, ball) && !m_IsEscaped)
		{
			m_IsEscaped = true;

		}
	}
	else if (m_Rotation == RotationState::d0)
	{
		if (utils::IsOverlapping(m_ExitBottom, ball) && !m_IsEscaped)
		{
			m_IsEscaped = true;

		}
	}
	if (m_IsA)
	{
		m_PosBall.x -= speed;
	}
	else if (m_IsD)
	{
		m_PosBall.x += speed;
	}
	for (int i{ 0 }; i < m_People.size(); ++i)
	{
		if (m_People[i] != nullptr)
		{
			if (m_People[i]->CollectPerson(ball))
			{
				++m_CollectedPeople;
				delete m_pScore;
				m_pScore = nullptr;
				m_pScore = new Texture("Score: " + std::to_string(m_CollectedPeople), "You escaped.otf", 25.f, Color4f{ 1,0,0,1 });
			}
			if (m_People[i]->IsPickedUp())
			{
				delete m_People[i];
				m_People[i] = nullptr;
			}
		}
		
		
	}
	
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
		utils::SetColor(Color4f(0,1,0,1));
		utils::FillRect(m_Exit);
	}
	glPopMatrix();

	utils::SetColor(Color4f(1.f, 0.f, 0.f, 1.f));
	
	utils::FillEllipse(m_PosBall.x, m_PosBall.y, 7.f,7.f);
	utils::SetColor(Color4f(0.f, 0.f, 0.f, 1.f));
	m_pMain->Draw();
	//utils::FillRect(m_Exit);
	
	if (m_IsEscaped)
	{
		
		m_pEscaped->Draw(Point2f(120,250));
	}
	utils::SetColor(Color4f(1, 0, 0, 1));
	/*utils::DrawRect(m_ExitBottom);
	utils::DrawRect(m_ExitLeft);
	utils::DrawRect(m_ExitTop);
	utils::DrawRect(m_ExitRight);*/
	for (int i{0}; i < m_People.size(); ++i)
	{
		if (m_People[i] != nullptr)
		{
			m_People[i]->Draw();
		}
		
	}
	m_pScore->Draw(Point2f(420.f,500.f));
	m_pTimer->Draw(Point2f(20.f,500.f));
	if (m_IsTimeUp)
	{
		m_pTimeUp->Draw(Point2f(120.f, 250.f));
	}
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	if (!m_IsTimeUp)
	{
		switch ( e.keysym.sym )
		{
			case SDLK_a:
				m_IsA = true;
		
				break;
			case SDLK_d:
				m_IsD = true;
	
				break;
		}
	}
	
}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
	if (!m_IsTimeUp)
	{
		switch (e.keysym.sym)
			{
			case SDLK_LEFT:
				std::cout << "Left arrow key released\n";
				for (int i{ 0 }; i < m_People.size(); ++i)
				{
					if (m_People[i] != nullptr)
					{
						m_People[i]->rotateCoins90Degrees(GetViewPort().width, GetViewPort().height);
					}
			
				}

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
				for (int i{ 0 }; i < m_People.size(); ++i)
				{
					if (m_People[i] != nullptr)
					{
						m_People[i]->rotateCoinsNeg90Degrees(GetViewPort().width, GetViewPort().height);
					}
			
				}
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
			case SDLK_a:
				m_IsA = false;
				break;
			case SDLK_d:
				m_IsD = false;
				break;
			}
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
