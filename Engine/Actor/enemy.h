#pragma once
#include "Object/Actor.h"

namespace nc 
{
	class enemy : public Actor
	{
	public:
		enemy() = default;
		virtual ~enemy() {}

		virtual eType GetType() { return eType::ENEMY; }


		virtual bool Load(const std::string& filename) override;

		virtual void Update(float dt) override;

		virtual void OnCollision(Actor* actor);

		void SetThrust(float thrust) { m_thrust = thrust; }

		void SetTarget(Actor* actor) { m_target = actor; };

	protected:
		float m_thrust{ 0.0f };
		Actor* m_target{ nullptr };
	};
}