#pragma once
#include "Object/Actor.h"
class Locator : public nc::Actor
{
public: 
	Locator() = default;
	virtual ~Locator() {}

	virtual eType GetType() { return eType::LOCATOR; }

	
	void Update(float dt) override;
};

