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
#include "ReflectObject.h"
#include "EnumMacro.h"
#include "StaticColumnarArray.h"
#include "Test.h"

using namespace ke;

int main() 
{
	HashGenerator<int> hashGenerator;
	BinHoodBucketNode<int, float, 16> node;
	node.insert(hashGenerator(0), 0, 10.f);
	node.insert(hashGenerator(1), 1, 20.f);




	Test a = Test();
	FlyweightStringA nameTestBool = Test::getNameTestBool;
	const char* strTestBool = nameTestBool.c_str();
	ReflectMetaData reflectMetaData = Test::getMetaData();
	bool t = false;	
}