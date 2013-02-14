#include "InGameLevel.h"

b2World* InGameLevel::physics = 0;
InGameLevel::InGameLevel()
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
	
	if(physics)
	{
		delete physics;
	}
	physics = new b2World(gravity);

	//------------------MORE LOADING!---------------
	player = new Player();
	player->Initialize();


	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0, 130.0f);
	b2Body * groundBody = physics->CreateBody(&groundBodyDef);

	b2PolygonShape groundBox;
	groundBox.SetAsBox(400.0f, 10.0f);

	groundBody->CreateFixture(&groundBox, 0.0f);
	//-------------------END LOADING---------------
	cam.SetAsCurrent();
	//cam.SetToTrack(player);
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