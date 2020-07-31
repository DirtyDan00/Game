#pragma once
#include "Object/Actor.h"

class Powerup : public nc::Actor
{
public:
	enum class ePowerType
	{
		RAPIDFIRE,
		DOUBLEPOINTS,
		INVCIBLITY
	};
public:

	Powerup() {}

	virtual void Update(float dt);

	virtual void OnCollision(Actor* actor);

	void SetPower(ePowerType power) { m_powerType = power; }

	virtual ePowerType GetPowerType() { return m_powerType; }

	virtual eType GetType() {
		return eType::POWERUP;
	}


protected:
	ePowerType m_powerType{ePowerType::RAPIDFIRE};
};