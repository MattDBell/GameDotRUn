//////////////////////////////////////////////////////////////////////////
//	Summary: In charge of receiving and deciphering events then sending them off
//
//	Responsibilities: Managing input, really.  Abstracting to allow for controller
//	ambiguous game code.
//
//////////////////////////////////////////////////////////////////////////

#ifndef INPUT_H
#define INPUT_H
#include <stdint.h>
//we're hijacking Renderers window, why?  Because all sf::window cares about is
//width, height and bpp on construction.  Things that the Renderer also cares
//about and things that the input doesn't.  That said we're hijacking it in the
//.cpp because we don't like polluting .h files.  Right?
const int MAX_CALLBACK = 5; //could do stuff with resizing arrays and what not but... nah
class Input
{
public:
	struct MouseEventParams 
	{
		uint32_t xPos	: 14; //Should be large enough. (0-16383)
		uint32_t yPos	: 14;
		uint32_t button : 4;
	};
	struct KeyEventParams
	{
		uint32_t	evt		: 20;   
		bool        alt		: 1;    
		bool        control : 1;
		bool        shift	: 1;  
		bool        system	: 1; 
	};
	union InputParams
	{
		MouseEventParams	mouse;
		KeyEventParams		key;
	};

	typedef void (*InputCallback)(InputParams parameters); 
	enum Events
	{
		ESC_KEY,
		W_KEY,
		A_KEY,
		S_KEY,
		D_KEY,
		TOTAL_EVENTS,
		REJECTED
	};
private:
	Input();
	static Input * instance;
	InputCallback callbacks[TOTAL_EVENTS][MAX_CALLBACK];
public:
	static Input * Get();
	bool GetEvents();
	uint32_t Register (Events evt, InputCallback callBack);
	void Unregister(Events evt, uint32_t handle);
};


#endif