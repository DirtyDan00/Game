#include "pch.h"
#include "player.h"
#include "Projectile.h"
#include "Object/Scene.h"
#include <fstream>
#include "Math/Math.h"

namespace nc 
{
	bool player::Load(const std::string& filename)
	{
		bool success = false;
		std::ifstream stream(filename);
		if (stream.is_open()) 
		{
			success = true;
			Actor::Load(stream);

			stream >> m_rotationRate;
			stream >> m_thrust;

			stream.close();
		}
		return success;
	}

	void player::Update(float dt)
	{
		nc::Vector2 force;
		m_fireTimer += dt;
		if (Core::Input::IsPressed(VK_SPACE) && m_fireTimer >= m_fireRate)
		{
			m_fireTimer = 0;
			Projectile* projectile = new Projectile;
			projectile->Load("projectile.txt");
			projectile->GetTransform().position = m_transform.position;
			projectile->GetTransform().angle = m_transform.angle;
			m_scene->AddActor(projectile);
		}

		//move player and enemy to toher classes, and add the m_volicty and m_thrust

		force = nc::Vector2::Rotate(force, m_transform.angle);
		m_transform.position = m_transform.position + force;

		if (Core::Input::IsPressed('W')) { force = nc::Vector2::forward * m_thrust; }
		force = nc::Vector2::Rotate(force, m_transform.angle);
		//force = force + nc::Vector2{ 0,100 }; wind LOL

		m_velocity = m_velocity + force * dt;
		m_velocity = m_velocity * 0.98f;
		m_transform.position = m_transform.position + m_velocity * dt;

		if (Core::Input::IsPressed('A')) { m_transform.angle = m_transform.angle - (dt * nc::DegreesToRadian(360.0f)); }
		if (Core::Input::IsPressed('D')) { m_transform.angle = m_transform.angle + (dt * nc::DegreesToRadian(360.0f)); }

		if (m_transform.position.x > 800) m_transform.position.x = 0;
		if (m_transform.position.x < 0) m_transform.position.x = 800;
		if (m_transform.position.y > 600) m_transform.position.y = 0;
		if (m_transform.position.y < 0) m_transform.position.y = 600;

		m_transform.Update();
	}

	void player::Draw(Core::Graphics& graphics)
	{
		m_shape.Draw(graphics, m_transform);
	}
}


