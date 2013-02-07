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
#include "GraphicsComponent.h"
#include "Pool.h"
class Input;

typedef bool (*keycomp)(const char *, const char *);

class Renderer
{
public:
	typedef Memory::Pool<GraphicsComponent, Memory::InitDefaultConstructor> GCPool;
private:
	sf::RenderWindow window;
	static Renderer * renderer;
	Renderer(int width, int height, int numComp = 100);
	GCPool pool;
	std::map<const char *, sf::Texture, keycomp> textures;
public:
	static void initialize(int width, int height, int numComp = 100);
	static Renderer * Get();
	bool IsOpen();
	sf::Texture* GetTexture(const char * filename);
	GCPool::Handle Create(char * fileName);
	void Draw(float deltaTime);
	friend class Input;
};
#endif