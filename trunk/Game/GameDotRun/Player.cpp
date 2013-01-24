#include "Player.h"
#include "Renderer.h"
#include "GraphicsComponent.h"

bool Player::Initialize()
{
	graphic = Renderer::Get()->Create("Animations\\player\\Player.xml");
	graphic->ChangeAnimation("Run");
	pos.SetX(0);
	pos.SetX(0);
	return true;
}
bool Player::Alive()
{
	return true;
}

bool Player::Update( float deltaTime )
{
	graphic->Draw(pos.AsSFML());
	return true;
}
bool Player::Spawn()
{
	return true;
}