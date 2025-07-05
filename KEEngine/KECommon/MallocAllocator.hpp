#include "MallocAllocator.h"
#include "MemoryCommon.h"

namespace ke
{	
	template<typename T>
	void* MallocAllocator<T>::allocate()
	{
		return KEMemory::aligendMalloc<T>(1);
	}
	template<typename T>
	void MallocAllocator<T>::deallocate(KE_IN void* ptr)
	{
		return delete(ptr, KEMemory::getSizeOfN<T>(1));
	}
}