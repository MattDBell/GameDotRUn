//////////////////////////////////////////////////////////////////////////
//	Summary: Top layer of any game mode (in game - main menu - etc)
//	
//	Responsibilities: The game loop.  Checks for transition conditions. Calls
//	Updates on any applicable managers.
//
//////////////////////////////////////////////////////////////////////////

#ifndef LEVEL_H
#define LEVEL_H

class Level
{
public:
	virtual void Load() = 0;
	virtual bool IsLoaded() = 0;
	virtual void Step(float deltaTime) = 0;
	virtual void Cleanup() = 0;
	virtual ~Level() {};
};

#endif