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
	constexpr int n = 10000000;
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
		std::cout << "Elapsed time: " << elapsed_seconds.count() << " seconds" << std::endl;
		bool test = true;
	}
	bool test = true;
	{
		unordered_map<double, int> stdMap;
		auto start = std::chrono::high_resolution_clock::now();
		for (int i = 0; i < n; ++i)
		{
			stdMap.insert({ static_cast<double>(i), i });
		}
		auto end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double>  elapsed_seconds = end - start;
		std::cout << "Elapsed time (std::unordered_map): " << elapsed_seconds.count() << " seconds" << std::endl;
		bool test = true;
	}

	test = true;
}