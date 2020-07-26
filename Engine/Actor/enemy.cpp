#include "pch.h"
#include "enemy.h"
#include "player.h"
#include "Math/Math.h"
#include "Object/Scene.h"
#include "Graphics/ParticleSystem.h"
#include "../Game.h"
#include <fstream>

namespace nc 
{

	bool enemy::Load(const std::string& filename)
	{
		bool success = false;
		std::ifstream stream(filename);

		if (stream.is_open())
		{
			success = true;

			Actor::Load(stream);

			stream >> m_thrust;

			stream.close();
		}

		return success;
	}

	void enemy::Update(float dt)
	{
		
		nc::Vector2 direction = m_target->GetTransform().position - m_transform.position;
		m_transform.angle = std::atan2(direction.y, direction.x) + nc::DegreesToRadian(-90.0f);
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

			nc::Color colors[] = { nc::Color::white,nc::Color::blue,nc::Color::green };
			nc::Color color = colors[rand() % 3];

			g_particleSystem.Create(m_transform.position, 0, 180, 30, color, 1, 100, 200);
		}
	}
}



