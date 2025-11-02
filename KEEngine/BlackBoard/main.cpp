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

using namespace std;
using namespace ke;

int main() 
{
	Test a = Test();
	const ReflectMetaData<Test>& reflectMetaData = Test::getMetaData();

	unordered_map<OwnedStringA, int> stdMap;
	stdMap.emplace("Test", 123);

	HashMap<OwnedStringA, int> testMap;
	testMap.insert("test", 123);
	HashSet<OwnedStringA> testSet;
	testSet.insert("test");

	ReadOnlyFile file("./test.xml");
	file.reader().readAll();
	file.reader().read(10, 10);

	WriteOnlyFile writeFile("./test_output.txt");
	writeFile.writer().write("Hello World!", 13);
	writeFile.writer().write("This is a test file.", 21);

	ReadWriteFile readWriteFile("./test_both.xml");
	readWriteFile.writer().write("Hello World!", 13);
	readWriteFile.writer().write("This is a test file.", 21);
	readWriteFile.reader().readAll();
	readWriteFile.writer().flush();
	readWriteFile.reader().readAll();

	bool test = true;
}