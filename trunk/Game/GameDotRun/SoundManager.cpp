#include "SoundManager.h"
#include "Debugging.h"
SoundManager* SoundManager::instance = 0;

SoundManager::SoundManager(int sBPSize, int sPSize)
	: sBufPool(sBPSize), sPool(sPSize)
{
}

void SoundManager::Initialize(int soundBufferPoolSize, int soundPoolSize)
{
	if(instance)
		DEBUGLOG("Debug.txt", "Recreating Sound Manager; this is probably a bug");
	instance = new SoundManager(soundBufferPoolSize, soundPoolSize);
}

SoundManager::SoundBufferPool::Handle SoundManager::Load(char * filename)
{
	//if already loaded (which it should be all but once.  Going to have to wrap the SoundBuffer class because it doesn't
	//keep track of the filename (rightfully so!)
	auto newBuffer = instance->sBufPool.GetNewItem();
	newBuffer->loadFromFile(filename);
	return newBuffer;
}

SoundManager::SoundPool::Handle SoundManager::Play(SoundManager::SoundBufferPool::Handle sound)
{
	auto newSound = instance->sPool.GetNewItem();
	newSound->setBuffer(*sound);
	return newSound;
}
void SoundManager::Release(SoundPool::Handle sound)
{
	instance->sPool.Release(sound);
}