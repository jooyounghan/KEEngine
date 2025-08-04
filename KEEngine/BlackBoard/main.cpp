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
	std::unordered_map<std::string, std::string> map;
	map.insert({ "one", "one" });
	map.insert({ "two", "two" });
	map.insert({ "three", "three" });

	std::unordered_map<std::string, std::string, HashConvertor<std::string>> customMap;
	customMap.insert({ "one", "one" });
	customMap.insert({ "two", "two" });
	customMap.insert({ "three", "three" });

	HashMap<int, int, int> test1;
	HashMap<int, int, BinHoodBucketNode<int, 64, 0.8f, 0.5f>> test2;
}