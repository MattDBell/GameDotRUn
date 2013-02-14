#ifndef POOL_H
#define POOL_H

#include "Debugging.h"
#include <stdint.h>

namespace Memory
{
	template<class T> 
	class InitNone
	{
	protected:
		~InitNone(){}
		void Init(void* Buffer){}
	};

	template<class T>
	class InitDefaultConstructor
	{
	protected: 
		~InitDefaultConstructor(){};
		void Init(void *Buffer)
		{
			new (Buffer) T();
		}
	};

	template<class T, template <class> class Initer = InitNone>
	class Pool : public Initer<T>
	{
		static_assert(sizeof(T) > 4, "sizeof T must be larger than 4");
		struct Node
		{
			T item;
			int& nextFree(){return *reinterpret_cast<int*>(&item);}
			bool used;
		};
		
		Node * nodes;
		uint32_t nextActive;
		uint32_t currentSize;
	public:

		class Handle
		{
		public:
			friend class Pool;
			Handle(): handle(0), m_pool(0){}
			bool IsValid() { return m_pool != 0;}
			T* operator->() { return &m_pool->nodes[handle].item;}
			T& operator*() {return m_pool->nodes[handle].item;}
		protected:
			Handle(Pool * pool, uint32_t index) : handle(index), m_pool(pool) {}
			uint32_t handle;
			Pool * m_pool;			
		};

		class Iterator : public Handle
		{
		protected:
			friend class Pool;
			Iterator(Pool * pool, uint32_t index): Handle(pool, index) {}
		public:
			Iterator(Handle& h) : Handle(h.m_pool, h.handle) {}
			void operator++() { while(!m_pool->nodes[++handle].used && handle != m_pool->currentSize);}
			void operator==(Iterator &rhs) { return handle == handle && m_pool == m_pool;}
			bool End() { return handle == m_pool->currentSize;}
		};

		typedef T* TemporaryItem;
		Pool(int initialSize)
			: nextActive(0), nodes(0)
		{
			nodes = reinterpret_cast<Node*>(malloc(sizeof(Node) * initialSize));
			if(nodes)
			{
				currentSize = initialSize;
				for(uint32_t i = 0; i < currentSize; ++i)
				{
					nodes[i].used = false;
					nodes[i].nextFree() = i +1;
				}
			}
			DEBUGLOG("Debug.txt", "Failed to allocate pool");
		}
	
		Handle GetNewItem()
		{
			if(nextActive == currentSize)
			{
				uint32_t targetSize = currentSize + (currentSize >> 2);
				Node* newNodes = reinterpret_cast<Node*>(malloc(sizeof(Node) * targetSize)); //grow by 25%
				if(newNodes)
				{
					memcpy(newNodes, nodes, sizeof(Node) * currentSize);
					for(uint32_t i = currentSize; i < targetSize; ++i)
					{
						newNodes[i].used = false;
						newNodes[i].nextFree() = i + 1;
					}
					currentSize = targetSize;
					DEBUGLOG("Debug.txt", "Pool is growing");
					nodes = newNodes;
					free(nodes);
				}
				else
				{
					DEBUGLOG("Debug.txt", "Failed to allocate new buffer, entering invalid state");
					return Handle();
				}
			}
			uint32_t h = nextActive;
			nextActive = nodes[nextActive].nextFree();
			Init(&nodes[h].item);
			return Handle(this, h);
		}
		void Release(Handle h)
		{
			nodes[h.handle].used = false;
			nodes[h.handle].nextFree() = nextActive;
			nextActive = h.handle;
			h.handle= 0;
			h.m_pool = 0;
		}
		Iterator Begin()
		{
			return Iterator(this, 0);
		}
	};
}


#endif//POOL_H