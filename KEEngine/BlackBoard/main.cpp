#include "../KECommon/OwnedString.h"
#include "../KECommon/BoundedString.h"
#include "../KECommon/PoolAllocator.h"
#include "../KECommon/Vector.h"
#include "../KECommon/OptionalValue.h"
#include "../KECommon/HashConvertor.h"
#include "../KECommon/OwnedString.h"
#include "../KECommon/HashMap.h"

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
	HashMap<int, int, BinHoodBucketNode<int, 64, 0.8f, 0.5f>, HashConvertor<int>> test;

	for (int i = 0; i < 100; i++)
	{
		test.insert(i, i);
	}
	for (int i = 0; i < 100; i++)
	{
		test.insert(i, i);
	}
	size_t test1 = test.getCount();
	while (true)
	{
	}
}