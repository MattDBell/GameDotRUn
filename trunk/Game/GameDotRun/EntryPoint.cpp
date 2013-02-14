#include <Windows.h>
#include <time.h>
#include "ApplicationLayer.h"
#include <Box2D/Box2D.h>

int CALLBACK WinMain( HINSTANCE /*hInstance*/, HINSTANCE /*hPrevInstance*/, LPSTR /*lpCmdLine*/, int /*nCmdShow*/)
{
	ApplicationLayer app(640, 480);
	app.Initialize();
	app.Run();

	//Leaving commented out as example code
	//b2Vec2 gravity(0.0f, -10.0f);
	//bool doSleep = true;
	//b2World world(gravity);
	//
	//b2BodyDef groundBodyDef;
	//groundBodyDef.position.Set(100.0f, 0.0f);
	//b2Body * groundBody = world.CreateBody(&groundBodyDef);
	//
	//b2PolygonShape groundBox;
	//groundBox.SetAsBox(50.0f, 10.0f);
	//groundBody->CreateFixture(&groundBox, 0.0f);
	//
	//b2BodyDef bodyDef;
	//bodyDef.type = b2_dynamicBody;
	//bodyDef.position.Set(100.0f, 100.0f);
	//b2Body * body = world.CreateBody(&bodyDef);
	//
	//b2PolygonShape dynamicBox;
	//dynamicBox.SetAsBox(1.0f, 1.0f);
	//
	//b2FixtureDef fixtureDef;
	//fixtureDef.shape = &dynamicBox;
	//fixtureDef.density = 1.0f;
	//fixtureDef.friction = 0.3f;
	//
	//body->CreateFixture(&fixtureDef);
	//
	//int32 velocityIterations = 6;
	//int32 positionIterations = 2;

	//There is also world.Step from box2d or some such,  GOt deleted and couldn't care less about it :P

	
	
	return 0;

}