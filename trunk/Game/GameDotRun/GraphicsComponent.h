//////////////////////////////////////////////////////////////////////////
//	Summary: From whence everything is drawn.  Also in charge of animation
//
//	Responsibilities: Draw to screen when told to and keep track of which
//	frame to draw
//
//////////////////////////////////////////////////////////////////////////

#ifndef GRAPHICS_COMPONENT_H
#define GRAPHICS_COMPONENT_H
#include <SFML\Graphics.hpp>
#include <stdint.h>
#include "Pool.h"

class Renderer;
class GraphicsComponent
{
public:
	struct AnimFrame
	{
		float time;
		sf::Sprite toDraw;
	};
	struct Animation
	{
		const char * name;
		//namehash eventually
		uint32_t numFrames;
		const char * nextAnim;
		bool loop;
		AnimFrame * frames;
	};
private:
	friend class Memory::InitDefaultConstructor<GraphicsComponent>;
	sf::Vector2<float> position;
	Animation * currAnimation;
	Animation * anims;
	uint32_t numAnims;
	float currTime;
	uint32_t currFrame;
	bool drawThisFrame;
	void Draw(sf::Vector2<float> camPosition, sf::RenderWindow* window, float deltaTime); //from Renderer
	GraphicsComponent();
	void SetNumAnims(uint32_t numAnims);
	friend class Renderer;
public:
	sf::Sprite* GetSprite();
	void SetAnim(uint32_t slot, Animation &anim);
	void ChangeAnimation(const char * newAnimState);
	void Draw(sf::Vector2<float> position, char * newAnimState = 0);
};
#endif