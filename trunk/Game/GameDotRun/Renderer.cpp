#include "Renderer.h"
#include "GraphicsComponent.h"
#include "tinyxml2.h"
Renderer * Renderer::renderer = 0;

Renderer * Renderer::Get()
{
	return renderer;
}

void Renderer::initialize(int width, int height)
{
	renderer = new Renderer(width, height);
}
bool Renderer::IsOpen()
{
	return window.isOpen();
}
sf::Sprite * Renderer::LoadSprite(const char * filename)
{
	sf::Texture temp;
	temp.loadFromFile(filename);
	return new sf::Sprite(temp);

}
GraphicsComponent * Renderer::Create(char * fileName)
{
	tinyxml2::XMLDocument file;
	file.LoadFile(fileName);
	
	tinyxml2::XMLElement * curr = file.FirstChildElement("Animation");
	uint32_t count = 0;
	for(tinyxml2::XMLElement * child = curr; child; child = child->NextSiblingElement("Animation"))
		++count;
	GraphicsComponent* comp = new GraphicsComponent();
	comp->anims = new GraphicsComponent::Animation[count];
	uint32_t index = 0;
	while(curr)
	{
		comp->anims[index].numFrames = curr->IntAttribute("numframes");
		comp->anims[index].name = curr->Attribute("name");
		comp->anims[index].loop = curr->BoolAttribute("loop");
		comp->anims[index].nextAnim = curr->Attribute("nextanim");
		comp->anims[index].frames = new GraphicsComponent::AnimFrame[comp->anims[index].numFrames];
		tinyxml2::XMLElement * frame = curr->FirstChildElement("Frame");
		uint32_t frameIndex = 0;
		while(frame)
		{
			comp->anims[index].frames[frameIndex].time = frame->FloatAttribute("time");
			comp->anims[index].frames[frameIndex].toDraw = LoadSprite(frame->Attribute("toDraw"));
			frame = frame->NextSiblingElement("Frame");
		}
		curr = curr->NextSiblingElement("Animation");
	}
	
	return 0; //FAILEDEDEDED
}
void Renderer::Draw()
{
	window.clear();
	//Draw all entities;
	window.display();
}
Renderer::Renderer(int width, int height)
	: window(sf::VideoMode(width, height), "SFML Works!")
{}