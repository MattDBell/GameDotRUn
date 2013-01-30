//////////////////////////////////////////////////////////////////////////
//	Summary: Entity is everything in the Level from platforms to players
//
//	Responsibilities: Handles entity specific logic and manages the group
//	of components that make it up (physics/graphics/sound(ish))

#ifndef ENTITY_H
#define ENTITY_H
#include <stdint.h>
#include "GDRVector2.h"
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
	T * ents;
	bool defrag;
	uint32_t poolSize;
	uint32_t nextActive;
	Creator	creatorForType;
public:

	EntityManager(uint32_t initialSize, Creator cForType, bool defrag = true)
		: defrag(defrag), poolSize(initialSize), nextActive(0) , creatorForType(cForType)
	{
		ents = new T[initialSize];
		memset(ents, 0, sizeof(T) * initialSize);
	}
	void Update(float deltaTime)
	{
		
		for(size_t i = 0; i < defrag? nextActive : poolSize; ++i)
		{
			if(!ents[i].Update(deltaTime))
			{
				if(defrag)
				{
					memcpy(ents[i], ents[--nextActive], sizeof(T));
					--i;
				}
			}
		}
	}
	Entity * Spawn(uint32_t type)
	{
		if(defrag)
		{
			if(nextActive == poolSize)
				return 0;
			ents[nextActive].Initialize();
			return &ents[nextActive++];
		}
		else
		{
			for(int i = 0; i < poolSize; ++i)
			{
				if(!ents[i].Alive())
				{
					ents[i].Initialize();
					return &ents[i];
				}
				return 0;
			}
		}
	}
};
#endif