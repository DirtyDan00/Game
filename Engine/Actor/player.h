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
		float m_rotationRate{360.0f};
		float m_fireRate{ 0.5f };
		float m_fireTimer{ 0.0f };
		nc::Vector2 m_velocity;
	};
}
