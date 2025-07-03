#include "MallocAllocator.h"
#include "MemoryCommon.h"

namespace ke
{	
	template<typename T>
	void* MallocAllocator<T>::allocate(KE_IN const size_t count)
	{
		return KEMemory::aligendMalloc<T>(count);
	}
	template<typename T>
	void MallocAllocator<T>::deallocate(KE_IN void* ptr, KE_IN const size_t count)
	{
		return delete(ptr, KEMemory::getSizeOfN<T>(count));
	}
}