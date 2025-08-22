#include "../KECommon/OwnedString.h"
#include "../KECommon/BoundedString.h"
#include "../KECommon/PoolAllocator.h"
#include "../KECommon/Vector.h"
#include "../KECommon/OptionalValue.h"
#include "../KECommon/HashGenerator.h"
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
		size_t count = 1000000;
		CompactHashMap<int, int, hash<int>> test;
		auto start = std::chrono::high_resolution_clock::now();
		for (int idx = 0; idx < count; ++idx)
		{
			test.insert(idx, idx);
		}
		auto end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> elapsed_seconds = end - start;
		std::cout << "HashMap Insert 걸린 시간: " << elapsed_seconds.count() << " 초, " << test.count() << std::endl;

		start = std::chrono::high_resolution_clock::now();
		for (int idx = 0; idx < count; ++idx)
		{
			test.remove(idx);
		}
		end = std::chrono::high_resolution_clock::now();
		elapsed_seconds = end - start;
		std::cout << "HashMap Remove 걸린 시간: " << elapsed_seconds.count() << " 초, " << test.count() << std::endl;

		std::unordered_map<int, int> stdTest;
		start = std::chrono::high_resolution_clock::now();
		for (int idx = 0; idx < count; ++idx)
		{
			stdTest.insert({ idx, idx });
		}
		end = std::chrono::high_resolution_clock::now();
		elapsed_seconds = end - start;
		std::cout << "unordered_map Insert 걸린 시간: " << elapsed_seconds.count() << " 초" << std::endl;
	
		start = std::chrono::high_resolution_clock::now();
		for (int idx = 0; idx < count; ++idx)
		{
			stdTest.erase(idx);
		}
		end = std::chrono::high_resolution_clock::now();
		elapsed_seconds = end - start;
		std::cout << "unordered_map Remove 걸린 시간: " << elapsed_seconds.count() << " 초" << std::endl;

		std::cout << " ===============================" << std::endl;
	}
}