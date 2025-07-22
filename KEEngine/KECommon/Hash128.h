#pragma once
#include "TypeCommon.h"

namespace ke
{
    class HashConvertor;

    class Hash128 
    {
        friend class HashConvertor;
    public:
		Hash128();
		Hash128(uint64 low, uint64 high);

    private:
        uint64 _low;
        uint64 _high;

    public:
        Hash128 operator^(uint8_t byte) const;
        Hash128& operator^=(uint8_t byte);
        Hash128 operator*(uint64 rhs) const;
        Hash128& operator*=(uint64 rhs);

    public:
        uint64 fold() const;
    };
}
