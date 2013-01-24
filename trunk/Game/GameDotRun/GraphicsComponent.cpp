#include "GraphicsComponent.h"
#include "Debugging.h"
GraphicsComponent::GraphicsComponent()
	:position(0, 0), currAnimation(0), anims(0), numAnims(0),currTime(0.0f), currFrame(0),
	drawThisFrame(false)
{

}
void GraphicsComponent::SetNumAnims(uint32_t numAnims)
{
	if(anims)
		DEBUGLOG("Debug.log", "SetNumAnims being called while anims != 0");
	this->numAnims = numAnims;
	anims = new Animation[numAnims];
	memset(anims, 0, sizeof(Animation) * numAnims);
}
sf::Sprite* GraphicsComponent::GetSprite()
{
	return &currAnimation->frames[currFrame].toDraw;
}
void GraphicsComponent::SetAnim(uint32_t slot, Animation &anim)
{
	memcpy(&anims[slot], &anim, sizeof(Animation));
}
void GraphicsComponent::ChangeAnimation(const char * newAnimState)
{
	for(size_t i = 0; i < numAnims; ++i)
	{
		if(anims[i].name && strcmp(anims[i].name, newAnimState) == 0)
		{
			currAnimation = &anims[i];
			return;
		}
	}
	DEBUGLOG("Debug", "Failed to find anim state");
}
void GraphicsComponent::Draw(sf::Vector2<float> position, char * newAnimState /* = 0 */)
{
	if(newAnimState)
	{
		ChangeAnimation(newAnimState);
	}
	this->position = position;
	drawThisFrame = true;
}
void GraphicsComponent::Draw(sf::Vector2<float> camPosition, sf::RenderWindow* window, float deltaTime)
{
	if(currAnimation)
	{
		currTime += deltaTime;
		float frameTime = currAnimation->frames[currFrame].time;
		if(currTime >= frameTime)
		{
			currTime -= frameTime;
			currFrame++;
			if(currFrame == currAnimation->numFrames)
			{
				if(currAnimation->loop)
					currFrame = 0;
				else
				{
					ChangeAnimation(currAnimation->nextAnim);
					currFrame = 0;
				}
			}
		}
	} 
	else 
	{
		return;
	}
	if(!drawThisFrame)
		return;
	sf::Sprite & drawing = currAnimation->frames[currFrame].toDraw;
	drawing.setPosition(position.x - camPosition.x, position.y - camPosition.y);
	window->draw(drawing);
	drawThisFrame = false;
}