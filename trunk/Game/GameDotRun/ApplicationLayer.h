//////////////////////////////////////////////////////////////////////////
//	Summary: Top most layer.  Application Layer is for all things not in an actual level.
//
//	Responsibilities:  Pre game menu flow.  Player Progression.  Level select/loading.
//	All file io should be done here (or called from here (Level.load("level.lvl"); would
//	be called from here.)
//
//////////////////////////////////////////////////////////////////////////

#ifndef APPLICATION_LAYER_H
#define APPLICATION_LAYER_H
#include "Level.h"
#include "Input.h"

class ApplicationLayer
{
	Level * currentLevel;
	static bool quit;
public:
	ApplicationLayer(int width, int height);
	void Initialize();
	void Run();
	bool InLevel();
	static void Quit(Input::InputParams params);

};
#endif