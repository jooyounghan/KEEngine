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
#include "HashMap.h"
#include "HashSet.h"
#include "File.h"

using namespace ke;

int main() 
{
	Test a = Test();
	const ReflectMetaData& reflectMetaData = Test::getMetaData();

	HashMap<OwnedStringA, int> testMap;
	testMap.insert("test", 123);
	HashSet<OwnedStringA> testSet;
	testSet.insert("test");

	File file("./test.xml");
	
}