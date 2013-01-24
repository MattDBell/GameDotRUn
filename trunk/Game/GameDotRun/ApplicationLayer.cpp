#include <Windows.h>
#include "ApplicationLayer.h"
#include "Renderer.h"
#include "InGameLevel.h"
#include <time.h>
bool ApplicationLayer::quit = false;

ApplicationLayer::ApplicationLayer(int width, int height)
	:currentLevel(0)
{
	Renderer::initialize(width, height);
}
void ApplicationLayer::Initialize()
{
	currentLevel = new InGameLevel();
	currentLevel->Load();
	return;
}
void ApplicationLayer::Run()
{
	quit = false;
	DWORD last = GetTickCount();
	Input::Get()->Register(Input::ESC_KEY, Quit);
	while(!quit)
	{
		Input::Get()->GetEvents();
		DWORD t = GetTickCount();
		float deltaTime = (t-last)/1000.0f;
		last = t;
		//Going to have to figure this out with Input
		//while(Renderer::PollEvent(evt))		
		//{										
		//	if(evt.type == sf::Event::Closed)	
		//		window.close();					
		//}
		if(InLevel())
		{
			currentLevel->Step(deltaTime);
		}
		Renderer::Get()->Draw(deltaTime);
		Sleep(16);
	}
}
bool ApplicationLayer::InLevel()
{
	return currentLevel != 0; //Pretty sure we aren't in a level yet.  AHAHHAAHAHAHAHAH!
}
void ApplicationLayer::Quit(Input::InputParams params)
{
	quit = true;
}