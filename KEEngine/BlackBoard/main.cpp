#include "../KECommon/PoolAllocator.hpp"

struct a
{
	size_t a;
	size_t b;

};

int main()
{
	ke::PoolAllocator<a, 5> allocator;

	while (true)
	{
		void* allocated = allocator.allocate();
		allocator.deallocate(allocated);
	}

	bool tset = true;

}