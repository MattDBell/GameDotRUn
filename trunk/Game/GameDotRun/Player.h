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
#include "Renderer.h"

class Player: public Entity
{
public:
	virtual bool Initialize();
	virtual bool Alive();
	virtual bool Spawn();
	virtual bool Update( float deltaTime );
};
#endif