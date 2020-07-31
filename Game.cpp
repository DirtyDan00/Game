#include "Game.h"
#include "Math/Math.h"
#include "Math/Random.h"
#include "Math/Vector2.h"
#include "Math/Color.h"
#include "Graphics/Shape.h"
#include "Math/Transform.h"
#include "Object/Actor.h"
#include "Actor/player.h"
#include "Actor/Locator.h"
#include "Actor/enemy.h"
#include "Object/Scene.h"
#include "Graphics/ParticleSystem.h"
#include "Audio/AudioSystem.h"
#include "Actor/PowerUp.h"
#include <list>
#include <string>
#include <iostream>

void Game::Startup()
{
	g_particleSystem.Startup();
	g_audioSystem.Startup();
	g_audioSystem.AddAudio("Laser", "Laser_Shoot.wav");
	g_audioSystem.AddAudio("Explosion", "Explosion.wav");
	g_audioSystem.AddAudio("Pickup", "Pickup.wav");
	//g_audioSystem.AddAudio("Theme", "Theme.wav");
	m_scene.StartUp();
	m_scene.SetGame(this);
}

void Game::Shutdonw()
{
	m_scene.Shutdown();
	g_particleSystem.Shutdown();
	g_audioSystem.Shutdown();
}

bool Game::Update(float dt)
{


	m_frametime = dt;

	bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);


	switch (m_state)
	{
	case Game::eState::INIT:
		//g_audioSystem.PlayAudio("Theme", true);
		m_state = eState::TITLE;
		break;
	case Game::eState::TITLE:
		if (Core::Input::IsPressed(VK_SPACE))
		{
			g_audioSystem.StopLoop();
			m_state = eState::START_GAME;
			m_score = 0;
			m_lives = 3;
		}
		break;
	case Game::eState::START_GAME:
	{
		nc::player* Player = new nc::player;
		Player->Load("player.txt");
		Locator* locator = new Locator;
		locator->GetTransform().position = nc::Vector2{ 3,2 };//affects the thruster particles
		//locator->GetTransform().angle = nc::DegreesToRadian(90);
		Player->AddChild(locator);

		locator = new Locator;
		locator->GetTransform().position = nc::Vector2{ -3,2 };//affects the thruster particles
		//locator->GetTransform().angle = nc::DegreesToRadian(90);
		Player->AddChild(locator);

		m_scene.AddActor(Player);
		for (int i = 0; i < 2; i++)
		{
			//nc::Actor* enemy = new enemy;
			//dynamic_cast<enemy*>(enemy)->
			//how to set a actor pointer
			nc::enemy* Enemy = new nc::enemy;
			Enemy->Load("enemy.txt");
			Enemy->SetTarget(m_scene.GetActor<nc::player>());

			float distance = nc::random(300, 600);
			float angle = nc::random(0, nc::TWO_PI);
			nc::Vector2 position = nc::Vector2::Rotate(nc::Vector2{ distance, 0.0f }, angle);

			Enemy->GetTransform().position = m_scene.GetActor<nc::player>()->GetTransform().position + position;
			m_scene.AddActor(Enemy);
		}

		
		m_state = eState::GAME;


	}
		break;
	case Game::eState::GAME:
		m_spawntimer += dt;
		if (m_spawntimer >= nc::random(1.5f, 2.0f))
		{
			//add enemy to scenes
			m_spawntimer = 0.0f;
			nc::enemy* Enemy = new nc::enemy;
			std::string enemies[] = { "enemy.txt", "smallEnemy.txt" };
			std::string enemyString = (m_score >= 500) ? enemies[rand() % 2] : enemies[0];
			Enemy->Load(enemyString);
			Enemy->SetTarget(m_scene.GetActor<nc::player>());
			float distance = nc::random(300, 600);
			float angle = nc::random(0, nc::TWO_PI);
			nc::Vector2 position = nc::Vector2::Rotate(nc::Vector2{ distance, 0.0f }, angle);

			Enemy->GetTransform().position = m_scene.GetActor<nc::player>()->GetTransform().position + position;
			m_scene.AddActor(Enemy);


		}
		m_spawnpowertimer += dt;
		if (m_spawnpowertimer >= nc::random(10.0f, 15.0f) && m_score >= 500)
		{
			m_spawnpowertimer = 0.0f;
			Powerup* powerup = new Powerup;
			Powerup::ePowerType types[] = { Powerup::ePowerType::DOUBLEPOINTS, Powerup::ePowerType::INVCIBLITY, Powerup::ePowerType::RAPIDFIRE };
			m_type = types[rand() % 3];
			std::string typesofpowerups[] = { "PowerUp.txt", "PowerUp2.txt", "PowerUp3.txt" };
			powerup->Load(typesofpowerups[static_cast<int> (m_type)]);
			powerup->SetPower(m_type);
			powerup->GetTransform().position = nc::Vector2{ nc::random(0,600), nc::random(0,400) };
			m_scene.AddActor(powerup);
		}

	

		break;
	case Game::eState::PLAYER_DEAD:
	{
		m_lives = m_lives - 1;
		m_state = (m_lives == 0) ? eState::GAME_OVER : eState::GAME_WAIT;
		m_stateTimer = 3.0f;
	}

		break;
	case Game::eState::GAME_WAIT:
		m_stateTimer -= dt;
		if (m_stateTimer <= 0)
		{
			m_scene.RemoveAllActors();
			m_state = eState::START_GAME;
		}
		break;
	case Game::eState::GAME_OVER:
		m_stateTimer -= dt;
		if (m_stateTimer <= 0)
		{
			m_scene.RemoveAllActors();
			m_state = eState::TITLE;
		}
		break;
	default:
		break;
	}
	

	
	nc::player* player = m_scene.GetActor<nc::player>();

	//if (Core::Input::IsPressed(Core::Input::BUTTON_LEFT))
	//{
	//	int x, y;
	//	Core::Input::GetMousePos(x, y);
	//
	//	nc::Color colors[] = { nc::Color::white,nc::Color::blue,nc::Color::green };
	//	nc::Color color = colors[rand() % 3];
	//
	//	g_particleSystem.Create(nc::Vector2{ x,y }, 0, 180, 30, color, 1, 100, 200);
	//}
	g_particleSystem.Update(dt);
	g_audioSystem.Update(dt);
	m_scene.Update(dt);

	return quit;
}

void Game::Draw(Core::Graphics& graphics)
{
	g_particleSystem.Draw(graphics);

	switch (m_state)
	{
	case Game::eState::INIT:
		break;
	case Game::eState::TITLE:
		graphics.SetColor(nc::Color::red);
		graphics.DrawString(325, 300, "INTERGALATIC CRUSADERS");
		break;
	case Game::eState::START_GAME:
		break;
	case Game::eState::GAME:
		break;
	case Game::eState::GAME_OVER:
		graphics.SetColor(nc::Color::red);
		graphics.DrawString(360, 300, "GAME OVER");
		break;
	default:
		break;
	}
		graphics.SetColor(nc::Color::white);
		graphics.DrawString(700, 10,("Score " + std::to_string(m_score)).c_str());
		graphics.DrawString(700, 20,("Lives " + std::to_string(m_lives)).c_str());
		m_scene.Draw(graphics);
}
