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

		HashMap<int, int, BinHoodBucketNode<int, int, 128>, hash<int>> test;
		auto start = std::chrono::high_resolution_clock::now();
		for (int idx = 0; idx < 10000; ++idx)
		{
			test.insert(idx, idx);
		}
		auto end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> elapsed_seconds = end - start;
		std::cout << "HashMap 걸린 시간: " << elapsed_seconds.count() << " 초" << std::endl;
		
		std::unordered_map<int, int> stdTest;
		start = std::chrono::high_resolution_clock::now();
		for (int idx = 0; idx < 10000; ++idx)
		{
			stdTest.insert({ idx, idx });
		}
		end = std::chrono::high_resolution_clock::now();
		elapsed_seconds = end - start;
		std::cout << "unordered_map 걸린 시간: " << elapsed_seconds.count() << " 초" << std::endl;



		for (int idx = 0; idx < 1000000; ++idx)
		{
			test.remove(idx);
		}
	}
}