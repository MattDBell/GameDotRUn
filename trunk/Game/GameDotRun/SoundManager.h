#ifndef SOUNDMANAGER
#define SOUNDMANAGER

#include "SFML/Audio.hpp"
#include "Pool.h"

class SoundManager
{
public:
	typedef Memory::Pool<sf::SoundBuffer, Memory::InitDefaultConstructor> SoundBufferPool;
	typedef Memory::Pool<sf::Sound, Memory::InitDefaultConstructor> SoundPool;
private:
	SoundBufferPool sBufPool;
	SoundPool sPool;
	static SoundManager* instance;
	SoundManager(int sBPSize, int sPSize);
public:
	static void Initialize(int soundBufferPoolSize, int soundPoolSize);
	static SoundBufferPool::Handle Load(char * filename); //This is a shared resource... Don't you dare Release it...
	static SoundPool::Handle Play(SoundBufferPool::Handle sound);
	static void Release(SoundPool::Handle sound);
};

#endif