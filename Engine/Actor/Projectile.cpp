#include "pch.h"
#include "Projectile.h"
#include "player.h"
#include "Math/Math.h"
#include "Graphics/ParticleSystem.h"
#include <fstream>

namespace nc 
{

	bool Projectile::Load(const std::string& filename)
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

	void Projectile::Update(float dt)
	{
		m_lifetime -= dt;
		if (m_lifetime <= 0)
		{
			m_destroy;
		}

		nc::Vector2 direction = nc::Vector2::Rotate(nc::Vector2::forward , m_transform.angle);
		nc::Vector2 ProjVelocity = direction * m_thrust;
		m_transform.position = m_transform.position + ProjVelocity * dt;
		g_particleSystem.Create(m_transform.position, m_transform.angle + nc::PI, 20, 1, nc::Color::blue, 1, 100, 200);

		


		m_transform.Update();
	}
	void Projectile::OnCollision(Actor* actor)
	{
		if (actor->GetType() == eType::ENEMY)
		{
			m_destroy = true;
		}
	}
}



