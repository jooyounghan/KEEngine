#include "MemoryCommon.h"

namespace ke
{
    NODISC size_t KEMemory::CalculateTargetCapacity(const size_t targetCount, const size_t currentCapacity)
    {
        if (targetCount > currentCapacity)
        {
            size_t newCapacity = targetCount + (targetCount >> 1) + (targetCount & 1);
            return (newCapacity > 0) ? newCapacity : 1u;
        }
        else
        {
            size_t shrinkThreshold = static_cast<size_t>(static_cast<float>(currentCapacity) * 0.5f);
            return (targetCount < shrinkThreshold) ? shrinkThreshold : currentCapacity;
        }
    }
}