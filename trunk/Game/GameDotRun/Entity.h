//////////////////////////////////////////////////////////////////////////
//	Summary: Entity is everything in the Level from platforms to players
//
//	Responsibilities: Handles entity specific logic and manages the group
//	of components that make it up (physics/graphics/sound(ish))

#ifndef ENTITY_H
#define ENTITY_H
#include <stdint.h>
#include "GDRVector2.h"
#include "Pool.h"
class Entity
{
	virtual bool Initialize() = 0;
	virtual bool Alive() = 0;
	virtual bool Spawn() = 0;
	virtual bool Update(float deltaTime) = 0;
public:
	virtual GDR_Vector2 GetPosition() const =0;

};

typedef Entity * (*Creator)();

template<typename T> // T is an Entity
class EntityManager
{
	typedef Memory::Pool<T> MPool;
	typedef typename MPool::Handle MHandle;
	MPool pool;
public:

	EntityManager(uint32_t initialSize, Creator cForType)
		: pool(initialSize)
	{
	}
	void Update(float deltaTime)
	{
		auto iter = pool.Begin();
		while(!iter.End())
		{
			if(!iter->Update(deltaTime))
			{
				pool.Release(iter);
			}
		}
	}
	MHandle Spawn()
	{
		return pool.GetNewItem();
	}
};
#endif