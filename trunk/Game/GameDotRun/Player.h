//////////////////////////////////////////////////////////////////////////
//	Summary: This is the player, shocker I know
//
//	Responsibilities: Act upon the player's input and represent him in the
//	Game world :P
//
//////////////////////////////////////////////////////////////////////////

#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "Box2D/Box2D.h"
#include "GDRVector2.h"
#include "Input.h"
#include "Renderer.h"

class Player: public Entity
{
	GDR_Vector2 pos;
	GDR_Vector2 movement;
	Renderer::GCPool::Handle graphic;
	b2Body * phys;
	static Player * playerOne;
public:
	static void InputHandleKeyBoard(Input::InputParams params);
	static void InputHandleMouse(Input::InputParams params);
	virtual bool Initialize();
	virtual bool Alive();
	virtual bool Spawn();
	virtual bool Update( float deltaTime );
	virtual GDR_Vector2 GetPosition() const { return pos;}
};
#endif