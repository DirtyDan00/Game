#pragma once
#include <graphics.h>
#include <vector>
#include <list>
class Game;
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
		void RemoveAllActors();
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
		void SetGame(Game* game) { m_game = game; }
		Game* GetGame() { return m_game; }

	private:
		Game* m_game;
		std::list<class Actor*> m_actors;
	};
}
