#include "MemoryCommon.h"

namespace ke
{
    NODISC size_t KEMemory::CalculateTargetCapacity(KE_IN const size_t targetCount, KE_IN const size_t currentCapacity)
    {
        if (targetCount > currentCapacity)
        {
            size_t newCapacity = targetCount + (targetCount >> 1) + (targetCount & 1);
            return (newCapacity > 0) ? newCapacity : 1u;
        }
        else
        {
            size_t shrinkThreshold = static_cast<size_t>(currentCapacity * 0.5f);
            return (targetCount < shrinkThreshold) ? shrinkThreshold : currentCapacity;
        }
    }

    NODISC void KEMemory::aligendFree(KE_IN void* ptr)
    {
        return _aligned_free(ptr);
    }
}