#include "../KECommon/OwnedString.h"
#include "../KECommon/BoundedString.h"
#include "../KECommon/PoolAllocator.h"
#include "../KECommon/Vector.h"

#include <cstdio>
#include <chrono>
#include <iostream>
#include <vector>
#include <string>

using namespace std;
using namespace ke;

int main()
{
	while (true)
	{
		Vector<int> vec;
		vec.reserve(1000000);
		for(int i = 0; i < 1000000; ++i)
		{
			vec.pushBack(i);
		}
		vec.resize(0);
	}
	constexpr int test = KEMath::GetNextPowerOf2(172918);
}