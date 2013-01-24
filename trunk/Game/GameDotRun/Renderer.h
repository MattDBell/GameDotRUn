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
#include <map>
class GraphicsComponent; //Almost want to include this but, may as well avoid pollution
class Input;

typedef bool (*keycomp)(const char *, const char *);

class Renderer
{
	sf::RenderWindow window;
	static Renderer * renderer;
	Renderer(int width, int height, int numComp = 100);
	GraphicsComponent * components;
	uint32_t numComps;
	uint32_t lastActive;
	std::map<const char *, sf::Texture, keycomp> textures;
	void SizeUp();
public:
	static void initialize(int width, int height, int numComp = 100);
	static Renderer * Get();
	bool IsOpen();
	sf::Texture* GetTexture(const char * filename);
	GraphicsComponent * Create(char * fileName);
	void Draw();
	friend class Input;
};
#endif