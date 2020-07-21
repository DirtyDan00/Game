#pragma once
#include <graphics.h>
#include <list>
namespace nc 
{
	class Scene
	{
	public: 
		void StartUp();
		void Shutdown();

		void Update(float dt);

		void Draw(Core::Graphics& graphics);

		void AddActor(class Actor* actor);
		void RemoveActor(class Actor* object);

		template <typename T>
		T* GetActor()
		{
			T* result{ nullptr };
			for (nc::Actor* actor : m_actors)
			{
				result = dynamic_cast<T*>(actor);
				if (result) break;
			}
			return result;
		}
		template <typename T>
		std::vector<T*> GetActors()
		{
			std::vector<T*> results;
			for (nc::Actor* actor : m_actors)
			{
				T* result = dynamic_cast<T*>(actor);
				if (result)
				{
					results.push_back(result);
				}
			}
			return results;
		}

	private:
		std::list<class Actor*> m_actors;
	};
}
