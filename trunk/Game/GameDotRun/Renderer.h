//////////////////////////////////////////////////////////////////////////
//	Summary: In charge of rendering.
//
//	Responsibilities:	Both Application and Game require rendering and they'll
//	both use the same window so we abstract all rendering away into a singleton.
//	This will also need to keep track of all 'active' shapes and draw them.
//
//////////////////////////////////////////////////////////////////////////

#ifndef RENDERER_H
#define RENDERER_H
#include <SFML/Graphics.hpp>
#include <stdint.h>
class GraphicsComponent; //Almost want to include this but, may as well avoid pollution
class Input;

class Renderer
{
	sf::RenderWindow window;
	static Renderer * renderer;
	Renderer(int width, int height);
	GraphicsComponent * components;
	uint32_t numComps;
	uint32_t lastActive;
public:
	static void initialize(int width, int height);
	static Renderer * Get();
	bool IsOpen();
	sf::Sprite * LoadSprite(const char * filename);
	GraphicsComponent * Create(char * fileName);
	void Draw();
	friend class Input;
};
#endif