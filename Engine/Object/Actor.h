#pragma once
#include "Graphics/Shape.h"
#include "Math/Transform.h"
#include "Object/Scene.h"
namespace nc
{
	class Scene;
	class Actor
	{
	public:
		enum class eType
		{
			PLAYER,
			ENEMY,
			PROJECTILE,
			LOCATOR,
			POWERUP
		};

	public:

		Transform transform;
		Shape shape;


		Actor() {}

		Actor(const Transform& transform, const Shape& shape) : m_transform{ transform }, m_shape{ shape }{};

		virtual ~Actor() {}

		virtual void Destroy();

		virtual eType GetType() = 0;

		virtual bool Load(const std::string& filename);

		virtual void Update(float dt);

		virtual void Draw(Core::Graphics& graphics);

		virtual void OnCollision(Actor* actor) {}

		virtual void Load(std::istream& stream);
		void SetScene(Scene* scene) { m_scene = scene; }
		Transform& GetTransform() { return m_transform; }
		float GetRadius();
		Shape& GetShape() { return m_shape; }

		void SetDestroy(bool destroy = true) { m_destroy = destroy; }
		bool IsDestroy() { return m_destroy; }

		void AddChild(Actor* child);
		Actor* GetParent() { return m_parent; }

	protected:
		bool m_destroy{false};
		Scene* m_scene{ nullptr };
		Transform m_transform;
		Shape m_shape;
		
		std::vector<Actor*> m_children; //vector good for going through big lists since theyre next to each other
		Actor* m_parent{nullptr};
	};
}
