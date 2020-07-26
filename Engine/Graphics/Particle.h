#pragma once
#include "Math/Color.h"
#include "Math/Vector2.h"
namespace nc 
{
	struct Particle
	{
		Vector2 prevPosition;
		Vector2 position;
		Vector2 velocity;
		Color color;
		float lifetime;
		float damping{ 0.98 };
		bool active{ false };
	};
}