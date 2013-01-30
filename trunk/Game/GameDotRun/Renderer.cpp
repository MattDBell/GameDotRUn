#include "Renderer.h"
#include "GraphicsComponent.h"
#include "tinyxml2.h"
#include "Hackery.h"
#include "Camera.h"

Renderer * Renderer::renderer = 0;

DelayDest(auto) textDir = MakeConstStr("Assets\\");

//static const char * textDir = "Assets/";

char* GetDir(const char * dir)
{
	int fileNameSize =strlen(dir);
	char * actFileName = new char[textDir.size + fileNameSize + 1];
	memcpy(actFileName, textDir.str, textDir.size);
	memcpy(&actFileName[textDir.size], dir, fileNameSize +1);
	return actFileName;
}

bool mapLess(const char * a, const char * b)
{
	return std::strcmp(a, b) < 0;
}
Renderer * Renderer::Get()
{
	return renderer;
}

void Renderer::initialize(int width, int height, int numComp /* = 100 */ )
{
	renderer = new Renderer(width, height,numComp);
}
bool Renderer::IsOpen()
{
	return window.isOpen();
}

void Renderer::SizeUp()
{
	int newSize = (int)(numComps * 1.25f);
	GraphicsComponent* newComps = new GraphicsComponent[newSize];
	memcpy(newComps, components, sizeof(GraphicsComponent) * numComps);
	delete[] components;
	components = newComps;
	numComps = newSize;
}
sf::Texture * Renderer::GetTexture(const char * filename)
{
	if(textures.count(filename))
		return &textures[filename];
	char * actFileName = GetDir(filename);
	textures[filename].loadFromFile(actFileName);
	delete actFileName;
	return &textures[filename];
}
GraphicsComponent * Renderer::Create(char * fileName)
{
	char * actDir = GetDir(fileName);
	tinyxml2::XMLDocument file;
	file.LoadFile(actDir);
	delete actDir;
	
	tinyxml2::XMLElement * curr = file.FirstChildElement("Animation");
	uint32_t count = 0;
	for(tinyxml2::XMLElement * child = curr; child; child = child->NextSiblingElement("Animation"))
		++count;
	if(lastActive > numComps)
		SizeUp();
	GraphicsComponent* comp = &components[lastActive++];
	comp->numAnims = count;
	comp->anims = new GraphicsComponent::Animation[count];
	uint32_t index = 0;
	while(curr)
	{
		comp->anims[index].numFrames = curr->IntAttribute("numframes");
		const char * n = curr->Attribute("name");
		
		comp->anims[index].name = new char[strlen(n) + 1];
		memcpy((void*)comp->anims[index].name, n, strlen(n) + 1);
		comp->anims[index].loop = curr->BoolAttribute("loop");
		comp->anims[index].nextAnim = curr->Attribute("nextanim");
		comp->anims[index].frames = new GraphicsComponent::AnimFrame[comp->anims[index].numFrames];
		tinyxml2::XMLElement * frame = curr->FirstChildElement("Frame");
		uint32_t frameIndex = 0;
		while(frame)
		{
			comp->anims[index].frames[frameIndex].time = frame->FloatAttribute("time");
			comp->anims[index].frames[frameIndex++].toDraw.setTexture(*GetTexture(frame->Attribute("image")));
			frame = frame->NextSiblingElement("Frame");
		}
		curr = curr->NextSiblingElement("Animation");
	}
	
	return comp;
}
void Renderer::Draw(float deltaTime)
{
	window.clear();
	Camera::UpdateCurrent(deltaTime);
	DelayDest(sf::Vector2<float>) camOff = Camera::GetOffset().AsSFML();
	//Draw all entities;
	for(uint32_t i = 0; i < lastActive; ++i)
	{
		components[i].Draw(camOff, &window, deltaTime);
	}
	window.display();
}
Renderer::Renderer(int width, int height, int numComp )
	: window(sf::VideoMode(width, height), "SFML Works!"), textures(mapLess)
{
	components = new GraphicsComponent[numComp];
	this->numComps = numComp;
	lastActive = 0;
	
}
