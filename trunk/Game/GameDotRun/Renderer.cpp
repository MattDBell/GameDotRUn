#include "Renderer.h"
#include "GraphicsComponent.h"
#include "tinyxml2.h"
Renderer * Renderer::renderer = 0;



template<int N>
struct ConstStr
{
	ConstStr (const char * str):str(str){}
	const char *str;
	enum { size = N -1};
};

template<int N>
const ConstStr<N>& MakeConstStr(const char (&str)[N] )
{
	ConstStr<N> *ret = new ConstStr<N>(&str[0]);
	return *ret;
}

const auto& textDir = MakeConstStr("Assets/");

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

void Renderer::initialize(int width, int height)
{
	renderer = new Renderer(width, height);
}
bool Renderer::IsOpen()
{
	return window.isOpen();
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
			comp->anims[index].frames[frameIndex].toDraw.setTexture(*GetTexture(frame->Attribute("image")));
			frame = frame->NextSiblingElement("Frame");
		}
		curr = curr->NextSiblingElement("Animation");
	}
	
	return comp;
}
void Renderer::Draw()
{
	window.clear();
	//Draw all entities;
	window.display();
}
Renderer::Renderer(int width, int height)
	: window(sf::VideoMode(width, height), "SFML Works!"), textures(mapLess)
{
	
}
