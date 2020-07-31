#pragma once
#include "core.h"
#include "Object/Scene.h"
#include "Actor/PowerUp.h"
class Game
{
public:
	enum class eState
	{
		INIT,
		TITLE,
		START_GAME,
		GAME,
		GAME_WAIT,
		PLAYER_DEAD,
		GAME_OVER
	};
public:
	void Startup();
	void Shutdonw();

	bool Update(float dt);
	void Draw(Core::Graphics& graphics);
	void AddPoints(int points) { m_score += points * m_multiplier; }
	void SetPointMultiplier(int multiplier) { m_multiplier = multiplier; }
	void SetState(eState state) { m_state = state; }
protected:
	eState m_state{ eState::TITLE };
	int m_lives{ 3 };
	int m_score{ 0 };
	int m_multiplier{ 1 };
	float m_stateTimer{ 0.0f };
	nc::Scene m_scene;

	float m_frametime;
	float m_spawntimer{ 0 };
	float m_spawnpowertimer{ 0 };
	float t{ 0 };
	DWORD prevTime;
	DWORD deltaTime;
	Powerup::ePowerType m_type;

};

