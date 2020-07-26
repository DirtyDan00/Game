#include "Game.h"
#include "Math/Math.h"
#include "Math/Random.h"
#include "Math/Vector2.h"
#include "Math/Color.h"
#include "Graphics/Shape.h"
#include "Math/Transform.h"
#include "Object/Actor.h"
#include "Actor/player.h"
#include "Actor/enemy.h"
#include "Object/Scene.h"
#include "Graphics/ParticleSystem.h"
#include <list>
#include <string>
#include <iostream>

void Game::Startup()
{
	g_particleSystem.Startup();
	m_scene.StartUp();
	m_scene.SetGame(this);
}

void Game::Shutdonw()
{
	m_scene.Shutdown();
	g_particleSystem.Shutdown();
}

bool Game::Update(float dt)
{


	m_frametime = dt;

	bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);


	switch (m_state)
	{
	case Game::eState::INIT:
		break;
	case Game::eState::TITLE:
		if (Core::Input::IsPressed(VK_SPACE))
		{
			m_state = eState::START_GAME;
		}
		break;
	case Game::eState::START_GAME:
	{
		nc::player* Player = new nc::player;
		Player->Load("player.txt");
		m_scene.AddActor(Player);
		for (int i = 0; i < 4; i++)
		{
			//nc::Actor* enemy = new enemy;
			//dynamic_cast<enemy*>(enemy)->
			//how to set a actor pointer
			nc::enemy* Enemy = new nc::enemy;
			Enemy->Load("enemy.txt");
			Enemy->SetTarget(m_scene.GetActor<nc::player>());
			Enemy->GetTransform().position = nc::Vector2{ nc::random(0,800), nc::random(0,600) };
			Enemy->SetThrust(nc::random(50, 100));
			m_scene.AddActor(Enemy);
		}
		m_state = eState::GAME;

	}
		break;
	case Game::eState::GAME:

		m_scene.Update(dt);

		break;
	case Game::eState::GAME_OVER:
		break;
	default:
		break;
	}
	

	m_spawntimer += dt;
	if (m_spawntimer >= nc::random(3.0f, 5.0f))
	{
		//add enemy to scenes
		m_spawntimer = 0.0f;
		nc::enemy* Enemy = new nc::enemy;
		Enemy->Load("enemy.txt");
		Enemy->SetTarget(m_scene.GetActor<nc::player>());
		Enemy->GetTransform().position = nc::Vector2{ nc::random(0,800), nc::random(0,600) };
		Enemy->SetThrust(nc::random(50, 125));
		m_scene.AddActor(Enemy);
	}
	nc::player* player = m_scene.GetActor<nc::player>();

	if (Core::Input::IsPressed(Core::Input::BUTTON_LEFT))
	{
		int x, y;
		Core::Input::GetMousePos(x, y);

		nc::Color colors[] = { nc::Color::white,nc::Color::blue,nc::Color::green };
		nc::Color color = colors[rand() % 3];

		g_particleSystem.Create(nc::Vector2{ x,y }, 0, 180, 30, color, 1, 100, 200);
	}
	g_particleSystem.Update(dt);

	return quit;
}

void Game::Draw(Core::Graphics& graphics)
{
	//graphics.SetColor(nc::Color{ 1,1,1 });
	//graphics.DrawString(10, 10, std::to_string(m_frametime).c_str());
	//graphics.DrawString(10, 20, std::to_string(1.0f /m_frametime).c_str());
	//graphics.DrawString(10, 30, std::to_string(deltaTime / 1000.0f).c_str());
	//
	//
	//float v = (std::sin(t) + 1.0f) * 0.5f;
	//nc::Vector2 p = nc::Lerp(nc::Vector2{ 400, 300 }, nc::Vector2{ 400, 100 }, v);
	////nc::Color pe = nc::Lerp(nc::Color{ 0,0,1 }, nc::Color{ 1, 0, 0 }, v);
	////graphics.SetColor(pe);
	//graphics.DrawString(p.x, p.y, "The Last Starfighter");
	g_particleSystem.Draw(graphics);

	switch (m_state)
	{
	case Game::eState::INIT:
		break;
	case Game::eState::TITLE:
		graphics.SetColor(nc::Color::green);
		graphics.DrawString(400, 300, "VECTORIDS");
		break;
	case Game::eState::START_GAME:
		break;
	case Game::eState::GAME:
		graphics.SetColor(nc::Color::white);
		graphics.DrawString(700, 10, std::to_string(m_score).c_str());
		m_scene.Draw(graphics);

		break;
	case Game::eState::GAME_OVER:
		graphics.SetColor(nc::Color::green);
		graphics.DrawString(400, 300, "GAME OVER");
		break;
	default:
		break;
	}
}
