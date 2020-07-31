#include "pch.h"
#include "player.h"
#include "Projectile.h"
#include "enemy.h"
#include "Object/Scene.h"
#include "../Game.h"
#include "Audio/AudioSystem.h"
#include "Actor/PowerUp.h"
#include <fstream>
#include <string>
#include "Math/Math.h"
#include "Graphics/ParticleSystem.h"

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

			//stream >> m_rotationRate;
			std::string line;
			std::getline(stream, line);
			m_rotationRate = stof(line);
			std::getline(stream, line);
			m_thrust = stof(line);
			std::getline(stream,line);
			m_fireRate = stof(line);
			//stream >> m_thrust;

			//std::getline(stream,line);
			//m_firerate = stof(line);
			//read in the line for the options

			stream.close();
		}
		return success;
	}

	void player::Update(float dt)
	{
		nc::Vector2 force;
		m_fireTimer += dt;
		m_rapidfire -= dt;
		m_invnci -= dt;
		m_doublepoint -= dt;
		m_scene->GetGame()->SetPointMultiplier((m_doublepoint > 0) ? 2 : 1);

		float fireRate = (m_rapidfire > 0) ? 0.2f : m_fireRate;
		if (Core::Input::IsPressed(VK_SPACE) && m_fireTimer >= fireRate)
		{
			m_fireTimer = 0;

			g_audioSystem.PlayAudio("Laser");
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
		//rotate
		float torque = 0;
		if (Core::Input::IsPressed('A')) { torque = -nc::DegreesToRadian(m_rotationRate); }
		if (Core::Input::IsPressed('D')) { torque = nc::DegreesToRadian(m_rotationRate); }

		m_angularVelocity = m_angularVelocity + torque * dt;
		m_angularVelocity = m_angularVelocity * 0.95f;
		m_transform.angle = m_transform.angle + m_angularVelocity * dt;

		//m_transform.position = nc::Clamp(m_transform.position, { 0,0 }, { 400, 300 });

		if (m_transform.position.x > 800) m_transform.position.x = 0;
		if (m_transform.position.x < 0) m_transform.position.x = 800;
		if (m_transform.position.y > 600) m_transform.position.y = 0;
		if (m_transform.position.y < 0) m_transform.position.y = 600;

		if (force.LengthSqr() > 0)
		{
			Actor* locator = m_children[0];
			g_particleSystem.Create(locator->GetTransform().matrix.GetPosition(), locator->GetTransform().matrix.GetAngle() + nc::PI, 20, 1, nc::Color::red, 1, 100, 200);

			locator = m_children[1];
			g_particleSystem.Create(locator->GetTransform().matrix.GetPosition(), locator->GetTransform().matrix.GetAngle() + nc::PI, 20, 1, nc::Color::red, 1, 100, 200);
		}

		m_transform.Update();

		for(Actor* child : m_children)
		{
			child->Update(dt);
		}
	}

	void player::OnCollision(Actor* actor)
	{
		if (actor->GetType() == eType::ENEMY && m_invnci < 0)
		{
			m_scene->GetGame()->SetState(Game::eState::PLAYER_DEAD);
			g_audioSystem.PlayAudio("Explosion");
			m_destroy = true;
			nc::Color colors[] = { nc::Color::white,nc::Color::blue,nc::Color::green };
			nc::Color color = colors[rand() % 3];

			g_particleSystem.Create(m_transform.position, 0, 180, 30, color, 1, 100, 200);


			auto enemies = m_scene->GetActors<nc::enemy>();
			for (auto enemy : enemies)
			{
				enemy->SetTarget(nullptr);
			}
		}
		if (actor->GetType() == eType::POWERUP)
		{
			Powerup* powerup = static_cast<Powerup*>(actor);

			Powerup::ePowerType currentPowerUp = powerup->GetPowerType();

			switch (currentPowerUp)
			{
			case Powerup::ePowerType::RAPIDFIRE:
				m_rapidfire = 15;
				break;
			case Powerup::ePowerType::DOUBLEPOINTS:
				m_doublepoint = 20;
				break;
			case Powerup::ePowerType::INVCIBLITY:
				m_invnci = 10;
				break;
			default:
				break;
			}

		}
	}

	void player::Draw(Core::Graphics& graphics)
	{
		m_shape.Draw(graphics, m_transform);
	}
}


