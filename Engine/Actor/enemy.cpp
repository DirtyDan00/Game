#include "pch.h"
#include "enemy.h"
#include "player.h"
#include "Math/Math.h"
#include "Object/Scene.h"
#include "Graphics/ParticleSystem.h"
#include "Audio/AudioSystem.h"
#include "../Game.h"
#include <fstream>

namespace nc 
{
	//if enemy isnt that different, just make another file diferenting it
	//if enemy is unquie, dirive it from the parent class as a child;
	bool enemy::Load(const std::string& filename)
	{
		bool success = false;
		std::ifstream stream(filename);

		if (stream.is_open())
		{

			success = true;

			Actor::Load(stream);

			std::string line;
			std::getline(stream, line);
			m_thrust = stof(line);

			stream.close();
		}

		return success;
	}

	void enemy::Update(float dt)
	{
		nc::Vector2 direction;
		if (m_target) 
		{
			direction = m_target->GetTransform().position - m_transform.position;
			m_transform.angle = std::atan2(direction.y, direction.x) + nc::DegreesToRadian(90.0f);
		}
		
		
		nc::Vector2 enemyVelocity = direction.Normalized() * m_thrust;
		m_transform.position = m_transform.position + (enemyVelocity * dt);
		m_transform.Update();
	}
	void enemy::OnCollision(Actor* actor)
	{
		if (actor->GetType() == eType::PROJECTILE)
		{
			m_destroy = true;
			m_scene->GetGame()->AddPoints(100);
			g_audioSystem.PlayAudio("Explosion");

			nc::Color colors[] = { nc::Color::white,nc::Color::blue,nc::Color::green };
			nc::Color color = colors[rand() % 3];

			g_particleSystem.Create(m_transform.position, 0, 180, 30, color, 1, 100, 200);
		}
	}
}



