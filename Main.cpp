// Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "core.h"
#include "Game.h"

Game game;

bool Update(float dt)// delta time 60 fps
{

	return game.Update(dt);
}

void Draw(Core::Graphics& graphics)
{
	game.Draw(graphics);

}
int main()
{

	game.Startup();


	char name[] = "CSC196";
	Core::Init(name, 800, 600);
	Core::RegisterUpdateFn(Update);
	Core::RegisterDrawFn(Draw);
	Core::GameLoop();
	game.Shutdonw();
	Core::Shutdown();
}