// Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "core.h"
#include <time.h>
#include "Game.h"
#include "Audio/AudioSystem.h"

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
	
	srand(static_cast<unsigned int>(time(NULL)));
	game.Startup();


	char name[] = "CSC196";
	Core::Init(name, 800, 600);
	Core::RegisterUpdateFn(Update);
	Core::RegisterDrawFn(Draw);
	Core::GameLoop();
	game.Shutdonw();
	Core::Shutdown();
}