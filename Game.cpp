// Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "core.h"
#include "Math/Math.h"
#include "Math/Random.h"
#include "Math/Vector2.h"
#include "Math/Color.h"
#include "Graphics/Shape.h"
#include "Math/Transform.h"
#include <string>
#include <iostream>

const size_t NUM_POINTS = 40;
std::vector<nc::Vector2> points = { };
nc::Color color{ 1, 0, 0 };
float speed = 5;
nc::Shape ship;  //add points here


nc::Transform transform{ {400, 300}, 4, 0 };

float frametime;
float roundTime{ 0 };
bool gameOver = false;


DWORD prevTime;
DWORD deltaTime;

bool Update(float dt)// delta time 60 fps
{
	//dt = current frame time - previous time
	DWORD time = GetTickCount();

	prevTime = time;


	frametime = dt;
	roundTime += dt;

	if (roundTime >= 5.0f) gameOver = true;
	if (gameOver) dt = 0;

	dt = dt * 2.0f;

	bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);

	int x;
	int y;

	Core::Input::GetMousePos(x,y);
	//
	//nc::Vector2 target = nc::Vector2{ x, y };
	//nc::Vector2 direction = target - position;

	nc::Vector2 force;

	nc::Vector2 direction = force;
	direction.Normalized();
	direction = nc::Vector2::Rotate(direction, transform.angle);
	transform.position = transform.position + direction;

	if (Core::Input::IsPressed('W')) { force = nc::Vector2::forward * speed * dt; }

	if (Core::Input::IsPressed('A')) { transform.angle = transform.angle - (dt * 3.0f); }
	if (Core::Input::IsPressed('D')) { transform.angle = transform.angle + (dt * 3.0f); }
	//if (Core::Input::IsPressed(Core::Input::KEY_LEFT)) { position -= nc::Vector2::left * speed * dt; }
	//if (Core::Input::IsPressed(Core::Input::KEY_RIGHT)) { position += nc::Vector2::right * speed * dt; }
	//if (Core::Input::IsPressed(Core::Input::KEY_UP)) { position += nc::Vector2::up * speed * dt; }
	//if (Core::Input::IsPressed(Core::Input::KEY_DOWN)) { position -= nc::Vector2::down * speed * dt; }

//	for (nc::Vector2& point : points)
//	{
//		point = { nc::random(-10.0f, 10.0f), nc::random(-10.0f, 10.0f) };
//	}
	return quit;
}

void Draw(Core::Graphics& graphics)
{
	graphics.DrawString(10, 10, std::to_string(frametime).c_str());
	graphics.DrawString(10, 20, std::to_string(1.0f / frametime).c_str());
	graphics.DrawString(10, 30, std::to_string(deltaTime / 1000.0f).c_str());


	if (gameOver) graphics.DrawString(400, 300, "Game Over");

	ship.Draw(graphics, transform);



	//bool isactive = false;
	//graphics.SetColor(RGB(rand() % 256, rand() % 256, rand() % 256)); 
	//graphics.DrawLine(static_cast<float>(rand() % 800), static_cast<float>(rand() % 600), 
	//static_cast<float>(rand() % 800), static_cast<float>(rand() % 600));

	//for (size_t i = 0; i < points.size() - 1; i++)
	//{
	//	//local / object stpace points
	//	nc::Vector2 p1 = points[i];
	//	nc::Vector2 p2 = points[i+1];
	//
	if (gameOver == true) (400, 300, "Game Over");
	//	//scale
	//	p1 = p1 * scale;
	//	p2 = p2 * scale;
	//	//rotate
	//	p1 = nc::Vector2::Rotate(p1, angle);
	//	p2 = nc::Vector2::Rotate(p2, angle);
	//
	//	//transform
	//	p1 = p1 + position;
	//	p2 = p2 + position;



		//graphics.DrawLine(p1.x, p1.y, p2.x, p2.y);
	//}
}
int main()
{

	//for (size_t i = 0; i < NUM_POINTS; i++)
	//for (size_t i = 0; i < NUM_POINTS; i++)
	//{
	//	points.push_back(nc::Vector2{ nc::random(0.0f, 800.0f), nc::random(0.0f, 600.0f) });
	//}
	//
	//nc::Vector2 point;
	//point.y = 6;
	//point.x = 4;

	DWORD ticks = GetTickCount();
	std::cout << ticks / 1000 / 60 / 60 << std::endl;
	prevTime = GetTickCount();

	ship.Load("ship.txt");


	char name[] = "CSC196";
	Core::Init(name, 800, 600);
	Core::RegisterUpdateFn(Update);
	Core::RegisterDrawFn(Draw);
	Core::GameLoop();
	Core::Shutdown();
}
