#include <array>
#include <cstdint>
#include <cstring>
#include <string>
#include <type_traits>
#include <iostream>
#include <string>
#include <random>
#include <limits>

#include "OwnedString.h"
#include "StringConvertor.h"
#include "StaticBuffer.h"
#include "ReflectMetaData.h"

using namespace ke;

int main()
{
	const char* i8str = "123~567";
	const char* fstr = "-0.9759~1.9754";

	int i81 = 123;
	float f1 = 0.9999f;
	int i82 = 567;
	float f2 = 1.9999f;


	RangedReflectProperty<int16> i16range("Int8RangeProperty", 100, -100);
	RangedReflectProperty<float> frange("FloatRangeProperty", 10.0f, -10.0f);

	i16range.setFromString(i8str);
	frange.setFromString(fstr);

	StaticBuffer<100> buffer;
	i16range.getToString(&buffer);
	OwnedStringA i16(buffer.getBuffer(), buffer.getCount());
	buffer.reset();

	frange.getToString(&buffer);
	OwnedStringA f(buffer.getBuffer(), buffer.getCount());
	buffer.reset();



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