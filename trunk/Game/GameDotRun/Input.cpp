#include "Input.h"
#include "SFML/Graphics.hpp"
#include "Renderer.h"
#include "Debugging.h"

Input::Events Translate (sf::Event evt, Input::InputParams & params)
{
	if(evt.type == sf::Event::KeyReleased)
	{
		switch(evt.key.code)
		{
		case sf::Keyboard::Escape:
			{
				params.key.code = evt.key.code;
				params.key.alt = evt.key.alt;
				params.key.control = evt.key.control;
				params.key.shift = evt.key.shift;
				params.key.system = evt.key.system;
				return Input::ESC_KEY;
			}
			
		}
	}
	return Input::REJECTED;
}

Input * Input::instance = 0;
Input::Input()
{
	memset(callbacks, 0, sizeof(InputCallback) * MAX_CALLBACK * (int)TOTAL_EVENTS );
}
Input * Input::Get()
{
	if(!instance)
		instance = new Input();
	return instance;
}
bool Input::GetEvents()
{
	static sf::RenderWindow *window = 0;
	if(!window)
	{
		window = &Renderer::Get()->window;
		if(!window)
			return false;
	}

	sf::Event evt;
	while(window->pollEvent(evt))
	{
		InputParams p;
		Events myEvent = Translate(evt, p);
		if(myEvent == REJECTED)
			continue;
		for(int i = 0; i < MAX_CALLBACK; ++i)
		{
			if(callbacks[(int)myEvent][i] != 0)
				callbacks[(int)myEvent][i](p);
		}
		//Translate and send off!
	}
	return true;
}
uint32_t Input::Register(Events evt, InputCallback callBack)
{
	for(int i = 0; i < MAX_CALLBACK; ++i)
	{
		if(callbacks[evt][i] == 0)
		{
			callbacks[evt][i] = callBack;
			return i;
		}
	}
	DEBUGLOG("Debug.log", "Registering callback failed");
	return -1;
}
void Input::Unregister(Events evt, uint32_t handle)
{
	DEBUGASSERT((handle >= 0) && (handle < 5), "Debug.log", "Handle not between 0 and 5");
	callbacks[evt][handle] = 0;
}