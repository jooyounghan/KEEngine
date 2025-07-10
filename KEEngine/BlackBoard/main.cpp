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
	ke::Vector<int> vec;
	vec.pushBack(1);
}