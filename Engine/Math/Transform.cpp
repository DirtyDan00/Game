#include "pch.h"
#include "Transform.h"

namespace nc
{
	std::istream& operator>>(std::istream& stream, Transform& transform)
	{
		stream >> transform.position;
		stream >> transform.scale;
		stream >> transform.angle;

		return stream;

		//player class
		//positon
		//angle
		//rotation
		//text file with it aka ship
	}

}