#include "../KECommon/Vector.h"
#include "../KECommon/PoolAllocator.h"
#include "../KECommon/TypeTraits.h"

class A {};
class B : public A {};
class C {};
class D : public C {};

int main()
{
	printf("%d\n", ke::KETrait::IsBaseOf<C, A>::value);
	printf("%d\n", ke::KETrait::IsBaseOf<C, B>::value);
	printf("%d\n", ke::KETrait::IsBaseOf<C, D>::value);

	ke::Vector<int> vec;
}