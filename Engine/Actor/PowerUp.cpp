#include "pch.h"
#include "PowerUp.h"
#include "Object/Scene.h"
#include "Actor/player.h"
#include "Audio/AudioSystem.h"

void Powerup::Update(float dt)
{
	m_transform.Update();
}

void Powerup::OnCollision(Actor* actor)
{
	if (actor->GetType() == eType::PLAYER)
	{
		m_destroy = true;
		g_audioSystem.PlayAudio("Pickup");
	}
}


