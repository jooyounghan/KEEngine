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
		StaticColumnarArray<100, int, float, double, char> columnarArray;

		columnarArray.getElement<0>(0) = 1;
		columnarArray.getElement<1>(0) = 2.1234f;
		columnarArray.getElement<2>(0) = 3.0;

		StaticColumnarArray<100, int, float, double, char> columnarArray2;
		columnarArray2.getElement<0>(0) = 10;
		columnarArray2.getElement<1>(0) = 20.1234f;
		columnarArray2.getElement<2>(0) = 30.0;

		StaticColumnarArray<100, int, float, double, char> columnarArray3 = columnarArray;
		columnarArray3 = columnarArray2;
		columnarArray2 = ke::move(columnarArray);
		std::cout << columnarArray2.getElement<0>(0) << std::endl;
		std::cout << columnarArray2.getElement<1>(0) << std::endl;
		std::cout << columnarArray2.getElement<2>(0) << std::endl;

	}
}