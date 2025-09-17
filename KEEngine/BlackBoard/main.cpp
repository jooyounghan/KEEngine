#include <array>
#include <cstdint>
#include <cstring>
#include <string>
#include <type_traits>
#include <iostream>
#include <string>
#include <random>
#include <limits>

#include "StringConvertor.h"
#include "StaticBuffer.h"
#include "ReflectMetaData.h"

int main()
{

	ke::StaticBuffer<1024> test;
	
	const char* test1 = "not fi fi fi fine not fi fi fine";

	test.write(reinterpret_cast<const void* const>(test1), strlen(test1));
	bool t = true;
}