#ifndef SOUNDMANAGER
#define SOUNDMANAGER

#include "SFML/Audio.hpp"
#include "Pool.h"



class SoundManager
{
public:
	static const int MAX_TRACKED = 16;
	typedef Memory::Pool<sf::SoundBuffer, Memory::InitDefaultConstructor> SoundBufferPool;
	typedef Memory::Pool<sf::Sound, Memory::InitDefaultConstructor> SoundPool;
private:
	SoundBufferPool sBufPool;
	SoundPool sPool;
	static SoundManager* instance;
	SoundManager(int sBPSize, int sPSize);
	SoundPool::Handle playing[MAX_TRACKED];
public:
	static void Initialize(int soundBufferPoolSize, int soundPoolSize);
	static SoundBufferPool::Handle Load(char * filename); //This is a shared resource... Don't you dare Release it...
	static SoundPool::Handle GetToPlay(SoundBufferPool::Handle sound);
	static void Clean();
	static void Release(SoundPool::Handle& sound);
	static bool PlayTilEnd(SoundPool::Handle sound);
};

#endif