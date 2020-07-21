// Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "core.h"
#include "Math/Math.h"
#include "Math/Random.h"
#include "Math/Vector2.h"
#include "Math/Color.h"
#include "Graphics/Shape.h"
#include "Math/Transform.h"
#include "Object/Actor.h"
#include "Actor/player.h"
#include "Actor/enemy.h"
#include "Object/Scene.h"
#include <list>
#include <string>
#include <iostream>


float t{ 0 };
float frametime;
float spawntimer{ 0 };
nc::Scene scene;



DWORD prevTime;
DWORD deltaTime;


bool Update(float dt)// delta time 60 fps
{


	frametime = dt;

	scene.Update(dt);
	

	bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);
	//if (Core::Input::IsPressed(VK_SPACE))
	//{
	//	//doesnt work
	//	nc::Actor* enemy = new nc::enemy;
	//	scene.RemoveActor(enemy);
	//
	//}
	spawntimer += dt;
	if (spawntimer >= nc::random(3.0f, 5.0f))
	{
		//add enemy to scenes
		spawntimer = 0.0f;
		nc::enemy* Enemy = new nc::enemy;
		Enemy->Load("enemy.txt");
		Enemy->SetTarget(scene.GetActor<nc::player>());
		Enemy->GetTransform().position = nc::Vector2{ nc::random(0,800), nc::random(0,600) };
		Enemy->SetThrust(nc::random(50, 125));
		scene.AddActor(Enemy);
	}
	scene.Update(dt);


	//Enemy.Update(dt);

	return quit;
}

void Draw(Core::Graphics& graphics)
{
	graphics.SetColor(nc::Color{ 1,1,1 });
	graphics.DrawString(10, 10, std::to_string(frametime).c_str());
	graphics.DrawString(10, 20, std::to_string(1.0f / frametime).c_str());
	graphics.DrawString(10, 30, std::to_string(deltaTime / 1000.0f).c_str());


	float v = (std::sin(t) + 1.0f)* 0.5f;
	nc::Vector2 p = nc::Lerp(nc::Vector2{ 400, 300 }, nc::Vector2{ 400, 100 }, v);
	//nc::Color pe = nc::Lerp(nc::Color{ 0,0,1 }, nc::Color{ 1, 0, 0 }, v);
	//graphics.SetColor(pe);
	graphics.DrawString(p.x, p.y, "The Last Starfighter");

	scene.Draw(graphics);
	//Enemy.Draw(graphics);

}
int main()
{


	DWORD ticks = GetTickCount();
	std::cout << ticks / 1000 / 60 / 60 << std::endl;
	prevTime = GetTickCount();

	scene.StartUp();

	nc::player* Player = new nc::player;
	Player->Load("player.txt");
	scene.AddActor(Player);

	for (int i = 0; i < 10; i++) 
	{
		//nc::Actor* enemy = new enemy;
		//dynamic_cast<enemy*>(enemy)->
		//how to set a actor pointer
		nc::enemy* Enemy = new nc::enemy;
		Enemy->Load("enemy.txt");
		Enemy->SetTarget(Player);
		Enemy->GetTransform().position = nc::Vector2{nc::random(0,800), nc::random(0,600)};
		Enemy->SetThrust(nc::random(50, 100));
		scene.AddActor(Enemy);
	}


	char name[] = "CSC196";
	Core::Init(name, 800, 600);
	Core::RegisterUpdateFn(Update);
	Core::RegisterDrawFn(Draw);
	Core::GameLoop();
	scene.Shutdown();
	Core::Shutdown();
}