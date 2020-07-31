#pragma once
#include "Object/Actor.h"
#include "Math/Vector2.h"

namespace nc 
{

	class player : public Actor
	{
	public:
		player() {}
		virtual ~player() {}
		virtual bool Load(const std::string& filename) override;
		virtual eType GetType() { return eType::PLAYER; }
		virtual void Update(float dt) override;

		virtual void OnCollision(Actor* actor);

		virtual void Draw(Core::Graphics& graphics) override;

	protected:
		float m_thrust{0.0f};
		float m_rotationRate{0.0f};
		float m_fireRate{ 0.0f };
		float m_fireTimer{ 0.0f };
		float m_rapidfire{ 0.0f };
		float m_invnci{ 0.0f };
		float m_doublepoint{ 0.0f };
		nc::Vector2 m_velocity;
		float m_angularVelocity{ 0.0f };
	};
}
