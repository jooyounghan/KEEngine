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
	while (true)
	{
		OptionalValue<int, uint8_t, size_t> test1;
		test1.setValue(1, 2, 3);
		OptionalValue<int, uint8_t, size_t> test2 = std::move(test1);

		//OptionalValue<size_t, int, uint8>test = OptionalValue<size_t, int, uint8>(4, 5, 6);
	}

	//HashMap<int, int, BinHoodBucketNode<int, 64, 0.8f, 0.5f>, HashConvertor<int>> test;
	//while (true)
	//{
	//	for (int i = 0; i < 100; i++)
	//	{
	//		test.insert(i, i);
	//	}
	//	size_t test1 = test.getCount();
	//	for (int i = 0; i < 100; i++)
	//	{
	//		test.insert(i, i);
	//	}

	//	test1 = test.getCount();
	//}

}