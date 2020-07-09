#pragma once
#include "Graphics/Shape.h"
#include "Math/Transform.h"
namespace nc
{
	class Actor
	{
	public:

		Transform transform;
		Shape shape;


		Actor() {}

		Actor(const Transform& transform, const Shape& shape) : m_transform{ transform }, m_shape{ shape }{};

	private:

		Transform m_transform;
		Shape m_shape;

	};
}
