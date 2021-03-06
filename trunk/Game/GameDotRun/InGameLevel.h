//////////////////////////////////////////////////////////////////////////
//	Summary:	Level in use when in the actual game.  This is where our game
//	logic goes
//
//	Responsibilities : Same as Level
//
//////////////////////////////////////////////////////////////////////////
#ifndef INGAMELEVEL_H
#define INGAMELEVEL_H
#include "Level.h"
#include <stdint.h>
#include "Box2D/Box2D.h"
#include "Player.h"
#include "Camera.h"
class InGameLevel : public Level
{
	static b2World* physics; //We may need to abstract this further
	int32_t velocityIter; 
	int32_t positionIter;
	Player * player;
	Camera cam;
public:
	InGameLevel();
	static b2World* GetPhysicsWorld(){return physics;}
	virtual void Load();
	virtual bool IsLoaded();
	virtual void Step(float deltaTime);
	virtual void Cleanup();
	virtual ~InGameLevel();
};
#endif