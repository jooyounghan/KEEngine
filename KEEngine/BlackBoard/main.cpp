#include "../KECommon/OwnedString.h"
#include "../KECommon/BoundedString.h"
#include "../KECommon/PoolAllocator.h"
#include "../KECommon/Vector.h"
#include "../KECommon/OptionalValue.h"
#include "../KECommon/HashGenerator.h"
#include "../KECommon/OwnedString.h"
#include "../KECommon/StringView.h"
#include "../KECommon/FlyweightString.h"
#include "../KECommon/HashMap.h"
#include "../KECommon/HashSet.h"
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


class Test
{
	const char* str1 = "Test";
};

class Test1
{
	OwnedStringA str1 = "Test";
};

class Test2
{
	FlyweightStringA str1 = "Test";
};


int main()
{
	{
		Test test[10000];
		bool a = true;
	}
	{
		Test1 test[10000];
		bool a = true;
	}
	{
		Test2 test[10000];
		bool a = true;
	}

	//while (true)
	//{
	//	size_t count = 1000000;
	//	CompactHashMap<int, int, HashGenerator<int>> test;
	//	CompactHashSet<int, HashGenerator<int>> testSet;
	//	std::unordered_map<int, int> stdTest;

	//	std::chrono::duration<double> elapsed_seconds;

	//	{
	//		auto start = std::chrono::high_resolution_clock::now();
	//		for (int idx = 0; idx < count; ++idx)
	//		{
	//			test.insert(idx, idx);
	//		}
	//		auto end = std::chrono::high_resolution_clock::now();
	//		elapsed_seconds = end - start;
	//		std::cout << "HashMap Insert 걸린 시간: " << elapsed_seconds.count() << " 초, " << test.count() << std::endl;

	//		start = std::chrono::high_resolution_clock::now();
	//		for (int idx = 0; idx < count; ++idx)
	//		{
	//			test.remove(idx);
	//		}
	//		end = std::chrono::high_resolution_clock::now();
	//		elapsed_seconds = end - start;
	//	}
	//	std::cout << "HashMap Remove 걸린 시간: " << elapsed_seconds.count() << " 초, " << test.count() << std::endl;


	//	{
	//		auto start = std::chrono::high_resolution_clock::now();
	//		for (int idx = 0; idx < count; ++idx)
	//		{
	//			testSet.insert(idx);
	//		}
	//		auto end = std::chrono::high_resolution_clock::now();
	//		elapsed_seconds = end - start;
	//		std::cout << "HashSet Insert 걸린 시간: " << elapsed_seconds.count() << " 초, " << testSet.count() << std::endl;

	//		start = std::chrono::high_resolution_clock::now();
	//		for (int idx = 0; idx < count; ++idx)
	//		{
	//			testSet.remove(idx);
	//		}
	//		end = std::chrono::high_resolution_clock::now();
	//		elapsed_seconds = end - start;
	//	}
	//	std::cout << "HashSet Remove 걸린 시간: " << elapsed_seconds.count() << " 초, " << testSet.count() << std::endl;

	//	{
	//		auto start = std::chrono::high_resolution_clock::now();
	//		for (int idx = 0; idx < count; ++idx)
	//		{
	//			stdTest.insert({ idx, idx });
	//		}
	//		auto end = std::chrono::high_resolution_clock::now();
	//		elapsed_seconds = end - start;
	//		std::cout << "unordered_map Insert 걸린 시간: " << elapsed_seconds.count() << " 초" << std::endl;
	//
	//		start = std::chrono::high_resolution_clock::now();
	//		for (int idx = 0; idx < count; ++idx)
	//		{
	//			stdTest.erase(idx);
	//		}
	//		end = std::chrono::high_resolution_clock::now();
	//		elapsed_seconds = end - start;
	//	}
	//	std::cout << "unordered_map Remove 걸린 시간: " << elapsed_seconds.count() << " 초" << std::endl;

	//	std::cout << " ===============================" << std::endl;
	//}
}