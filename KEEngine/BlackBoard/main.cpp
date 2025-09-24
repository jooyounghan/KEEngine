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

using namespace ke;

int main()
{
	ReflectMetaData meta;
	while (true)
	{
		int32 int1;
		int32 int2;
		int32 int3;
		int32 int4;
		int32 int5;
		ReflectParser::parseFromString("1~2~3~4~5", int1, int2, int3, int4, int5);
	}
	bool test = true;
}