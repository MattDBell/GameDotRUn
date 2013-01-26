#include "Player.h"
#include "Renderer.h"
#include "GraphicsComponent.h"
#include "Hackery.h"
#include "InGameLevel.h"
bool Player::Initialize()
{
	DelayDest(auto) animStart = MakeConstStr("Run");
	graphic = Renderer::Get()->Create("Animations\\player\\Player.xml");
	graphic->ChangeAnimation(animStart.str);
	pos.SetX(0);
	pos.SetY(0);

	b2BodyDef bDef;
	bDef.type = b2_dynamicBody;
	bDef.userData =(void*)(static_cast<Entity*>(this)); //Just in case we decide to do multiple inheritance :P
	bDef.position.Set(0.0f, 4.0f);
	b2World* w = InGameLevel::GetPhysicsWorld();
	phys = w->CreateBody(&bDef);
	b2CircleShape bottom;
	bottom.m_p = b2Vec2(0, 0.5f);
	bottom.m_radius = 0.5f;
	phys->CreateFixture(&bottom, 1.0f);
	b2CircleShape top;
	top.m_p = b2Vec2(0, -0.5f);
	top.m_radius = 0.5f;
	phys->CreateFixture(&top, 1.0f);
	b2PolygonShape middle;
	middle.SetAsBox(0.5f, 1.0f);
	phys->CreateFixture(&middle, 1.0f);

	return true;
}
bool Player::Alive()
{
	return true;
}

bool Player::Update( float deltaTime )
{
	pos.AsBox() = phys->GetPosition();
	DelayDest(sf::Vector2<float>) posSF = pos.AsSFML();
	graphic->Draw(posSF);
	return true;
}
bool Player::Spawn()
{
	return true;
}