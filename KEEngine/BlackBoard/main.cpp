#include "../KECommon/OwnedString.h"
#include "../KECommon/BoundedString.h"
#include "../KECommon/PoolAllocator.h"
#include "../KECommon/Vector.h"
#include "../KECommon/OptionalValue.h"
#include "../KECommon/HashGenerator.h"
#include "../KECommon/OwnedString.h"
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


int main()
{
	while (true)
	{
		size_t count = 1000000;
		CompactHashMap<int, int, hash<int>> test;
		CompactHashSet<int, hash<int>> testSet;
		std::unordered_map<int, int> stdTest;

		std::chrono::duration<double> elapsed_seconds;

		{
			auto start = std::chrono::high_resolution_clock::now();
			for (int idx = 0; idx < count; ++idx)
			{
				test.insert(idx, idx);
			}
			auto end = std::chrono::high_resolution_clock::now();
			elapsed_seconds = end - start;
			std::cout << "HashMap Insert �ɸ� �ð�: " << elapsed_seconds.count() << " ��, " << test.count() << std::endl;

			start = std::chrono::high_resolution_clock::now();
			for (int idx = 0; idx < count; ++idx)
			{
				test.remove(idx);
			}
			end = std::chrono::high_resolution_clock::now();
			elapsed_seconds = end - start;
		}
		std::cout << "HashMap Remove �ɸ� �ð�: " << elapsed_seconds.count() << " ��, " << test.count() << std::endl;


		{
			auto start = std::chrono::high_resolution_clock::now();
			for (int idx = 0; idx < count; ++idx)
			{
				testSet.insert(idx);
			}
			auto end = std::chrono::high_resolution_clock::now();
			elapsed_seconds = end - start;
			std::cout << "HashSet Insert �ɸ� �ð�: " << elapsed_seconds.count() << " ��, " << testSet.count() << std::endl;

			start = std::chrono::high_resolution_clock::now();
			for (int idx = 0; idx < count; ++idx)
			{
				testSet.remove(idx);
			}
			end = std::chrono::high_resolution_clock::now();
			elapsed_seconds = end - start;
		}
		std::cout << "HashSet Remove �ɸ� �ð�: " << elapsed_seconds.count() << " ��, " << testSet.count() << std::endl;

		{
			auto start = std::chrono::high_resolution_clock::now();
			for (int idx = 0; idx < count; ++idx)
			{
				stdTest.insert({ idx, idx });
			}
			auto end = std::chrono::high_resolution_clock::now();
			elapsed_seconds = end - start;
			std::cout << "unordered_map Insert �ɸ� �ð�: " << elapsed_seconds.count() << " ��" << std::endl;
	
			start = std::chrono::high_resolution_clock::now();
			for (int idx = 0; idx < count; ++idx)
			{
				stdTest.erase(idx);
			}
			end = std::chrono::high_resolution_clock::now();
			elapsed_seconds = end - start;
		}
		std::cout << "unordered_map Remove �ɸ� �ð�: " << elapsed_seconds.count() << " ��" << std::endl;

		std::cout << " ===============================" << std::endl;
	}
}