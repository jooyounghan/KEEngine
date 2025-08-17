#include "../KECommon/OwnedString.h"
#include "../KECommon/BoundedString.h"
#include "../KECommon/PoolAllocator.h"
#include "../KECommon/Vector.h"
#include "../KECommon/OptionalValue.h"
#include "../KECommon/HashConvertor.h"
#include "../KECommon/OwnedString.h"
#include "../KECommon/HashMap.h"
#include "../KECommon/StaticArray.h"
#include "../KECommon/StaticColumnarArray.h"

#include <cstdio>
#include <chrono>
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;
using namespace ke;


int main()
{
	while (true)
	{
		HashMap<int, int, BinHoodBucketNode<int, int, 64>, HashConvertor<int>> test;
		for (int idx = 0; idx < 100; ++idx)
		{
			test.insert(idx, idx);
		}
		size_t count = test.getCount();
		for (int idx = 0; idx < 100; ++idx)
		{
			test.remove(idx);
		}
		count = test.getCount();
	}
}