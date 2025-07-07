#include "../KECommon/Vector.h"
#include "../KECommon/PoolAllocator.h"
#include "../KECommon/TypeTraits.h"

struct a
{
	size_t a;
	size_t b;

};

int main()
{
	ke::PoolAllocator<size_t, 10> poolAllocator;
	void* m1 = poolAllocator.allocate(5);
	void* m2 = poolAllocator.allocate(5);
	poolAllocator.deallocate(m1, 5);
	void* m3 = poolAllocator.allocate(8);
	void* m4 = poolAllocator.allocate(3);
	void* m5 = poolAllocator.allocate(3);
	void* m6 = poolAllocator.allocate(2);
	void* m7 = poolAllocator.allocate(1);
	poolAllocator.deallocate(m2, 5);
	void* m8 = poolAllocator.allocate(1);
	void* m9 = poolAllocator.allocate(5);
	void* m10 = poolAllocator.allocate(2);
	void* m11 = poolAllocator.allocate(6);
	void* m12 = poolAllocator.allocate(2);
	poolAllocator.deallocate(m10, 2);
	void* m13 = poolAllocator.allocate(3);
	void* m14 = poolAllocator.allocate(2);
}