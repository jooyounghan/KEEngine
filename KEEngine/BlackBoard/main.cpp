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
	const char* i8str = "123~567";
	const char* fstr = "0.9999~1.9999";

	int i81 = 123;
	float f1 = 0.9999f;
	int i82 = 567;
	float f2 = 1.9999f;


	RangedReflectProperty<int8> i8range("Int8RangeProperty", 100, -100);
	RangedReflectProperty<float> frange("FloatRangeProperty", 10.0f, -10.0f);

	i8range.setFromString(i8str);
	frange.setFromString(fstr);

	//ReflectProperty<int8> i8test("Int8TestProperty", 0);
	//ReflectProperty<float> ftest("FloatTestProperty", 0);

	////i8test.setFromString(i8str);
	////ftest.setFromString(fstr);

	//i8test.setFromBinary(&i8);
	//ftest.setFromBinary(&f);

	//StaticBuffer<100> buffer;
	//i8test.getToString(&buffer);
	//buffer.writeOne('/');
	//ftest.getToString(&buffer);

	bool test = true;
}