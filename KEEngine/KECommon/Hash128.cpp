#include "Hash128.h"

namespace ke
{
	Hash128::Hash128() : _low(0), _high(0) {}
	Hash128::Hash128(uint64 low, uint64 high) : _low(low), _high(high) {}

    Hash128 Hash128::operator^(uint8_t byte) const
    {
        return { _low ^ byte, _high };
    }

    Hash128& Hash128::operator^=(uint8_t byte)
    {
        _low ^= byte;
        return *this;
    }

    Hash128 Hash128::operator*(uint64 rhs) const 
    {
        uint64_t a = _low & 0xFFFFFFFFULL;
        uint64_t b = _low >> 32;

        uint64_t ra = rhs & 0xFFFFFFFFULL;
        uint64_t rb = rhs >> 32;

        uint64_t a_rb = a * rb;
        uint64_t b_ra = b * ra;

        uint64_t lowPart = _low * rhs;
        uint64_t mid = a_rb + b_ra;

        uint64_t highPart = _high * rhs + mid + (_low >> 32) * (rhs >> 32);

        return { lowPart, highPart };
    }

    Hash128& Hash128::operator*=(uint64 rhs) 
    {
        *this = (*this) * rhs;
        return *this;
    }


    uint64 Hash128::fold() const
    {
        return _low ^ _high;
    }
}
