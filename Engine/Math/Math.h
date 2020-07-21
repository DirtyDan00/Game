#pragma once
#include "Math/Vector2.h"
namespace nc 
{

		const float PI = 3.1415f;
		const float TWO_PI = PI * 2;
		const float HALF_PI = PI * 0.5f;

		inline float RadiansToDegrees(float radians)
		{
			return radians * (180.0f / PI);
		}

		inline float DegreesToRadian(float degrees)
		{
			return degrees * (PI / 180.0f);
		}
		template <typename T>
		inline T Clamp(T v, T min, T max)
		{
			if (v < min) v = min;
			if (v < max) v = max;

			return v;

		}

		template<>

		inline nc::Vector2 Clamp<nc::Vector2>(nc::Vector2 v, nc::Vector2 min, nc::Vector2 max)
		{
			v.x = Clamp(v.x, min.x, max.x);
			v.x = Clamp(v.y, min.y, max.y);

			return v;
		}

		template<typename T>
		inline T Lerp(T a, T b, float t) 
		{
			return (a + ((b - a) * t));
		}

}

