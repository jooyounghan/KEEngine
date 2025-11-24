#include <array>
#include <cstdint>
#include <cstring>
#include <string>
#include <type_traits>
#include <iostream>
#include <string>
#include <random>
#include <limits>
#include <unordered_map>
#include <chrono>

#include "OwnedString.h"
#include "StringConvertor.h"
#include "StaticBuffer.h"
#include "ReflectObject.h"
#include "EnumMacro.h"
#include "StaticColumnarArray.h"
#include "Test.h"
#include "HashContainer.h"
#include "File.h"

using namespace std;
using namespace ke;


int main() 
{
	constexpr int n = 1000000;
	{
		HashMap<double, int, 128> testMap;
		auto start = std::chrono::high_resolution_clock::now();
		for (int i = 0; i < n; ++i)
		{
			testMap.insert(static_cast<double>(i), i);
		}
		auto end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> elapsed_seconds = end - start;

		std::cout << std::fixed << std::setprecision(3);
		std::cout << "Elapsed time For Insert Of HashMap: " << elapsed_seconds.count() << " seconds" << std::endl;
		
		start = std::chrono::high_resolution_clock::now();
		for (int i = 0; i < n; ++i)
		{
			HashBucketFindResult<double, int> findResult = testMap.find(static_cast<double>(i));
			if (findResult._keyPtr == nullptr)
			{
				std::cout << "Error: Key " << i << " not found or value mismatch." << std::endl;
			}
		}

		end = std::chrono::high_resolution_clock::now();
		elapsed_seconds = end - start;

		std::cout << std::fixed << std::setprecision(3);
		std::cout << "Elapsed time For Find Of HashMap: " << elapsed_seconds.count() << " seconds" << std::endl;
		bool test = true;
	}
	bool test = true;
	{
		unordered_map<double, int, HashGenerator<double>> stdMap;
		auto start = std::chrono::high_resolution_clock::now();
		for (int i = 0; i < n; ++i)
		{
			stdMap.insert({ static_cast<double>(i), i });
		}
		auto end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double>  elapsed_seconds = end - start;
		std::cout << "Elapsed time For Insert(std::unordered_map): " << elapsed_seconds.count() << " seconds" << std::endl;

		start = std::chrono::high_resolution_clock::now();
		for (int i = 0; i < n; ++i)
		{
			auto it = stdMap.find(static_cast<double>(i));
			if (it == stdMap.end() || it->second != i)
			{
				std::cout << "Error: Key " << i << " not found or value mismatch." << std::endl;
			}
		}
		end = std::chrono::high_resolution_clock::now();
		elapsed_seconds = end - start;
		std::cout << "Elapsed time For Find(std::unordered_map): " << elapsed_seconds.count() << " seconds" << std::endl;

		bool test = true;
	}
	test = true;
}