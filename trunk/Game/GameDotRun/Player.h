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
class GraphicsComponent;

class Player: public Entity
{
	GDR_Vector2 pos;
	GraphicsComponent * graphic;
public:
	virtual bool Initialize();
	virtual bool Alive();
	virtual bool Spawn();
	virtual bool Update( float deltaTime );
};
#endif