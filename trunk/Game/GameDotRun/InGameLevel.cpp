#include "InGameLevel.h"

InGameLevel::InGameLevel()
	: physics(0)
{}
bool InGameLevel::IsLoaded()
{
	return true; //woop woop
}
void InGameLevel::Load()
{
	//-------REPLACE ALL WITH LOADING -------
	b2Vec2 gravity(0, 10.0f);
	velocityIter = 6;
	positionIter = 2;
	//------- END LOADING -------
	
	physics = new b2World(gravity);
	player = new Player();
	player->Initialize();
}
void InGameLevel::Step(float deltaTime)
{
	physics->Step(deltaTime, velocityIter, positionIter);
	player->Update(deltaTime);
}
void InGameLevel::Cleanup()
{
	if(physics != 0)
		delete physics;
	physics = 0;
	return;
}
InGameLevel::~InGameLevel()
{
	if(physics != 0)
		delete physics;
	physics = 0;
}