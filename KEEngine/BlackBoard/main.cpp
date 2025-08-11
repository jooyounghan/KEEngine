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
	StaticArray<10, int> staticArray;
	staticArray[0] = 1;
	std::cout << staticArray[0] << std::endl;
	staticArray[0] = 2;
	std::cout << staticArray[0] << std::endl;
	StaticColumnarArray<100, int, float, double, char> columnarArray;

	columnarArray.getElement<0>(0) = 1;
	columnarArray.getElement<1>(0) = 2.1234f;
	columnarArray.getElement<2>(0) = 3.0;

	std::cout << columnarArray.getElement<0>(0) << std::endl;
	std::cout << columnarArray.getElement<1>(0) << std::endl;
	std::cout << columnarArray.getElement<2>(0) << std::endl;

	while (true)
	{
		OptionalValue<int, uint8_t, size_t> test1;
		test1.setValue(1, 2, 3);
		OptionalValue<int, uint8_t, size_t> test2 = std::move(test1);

		Vector<int> vec;
		vec.pushBack(1);
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