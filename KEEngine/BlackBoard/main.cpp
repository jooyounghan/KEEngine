#include "../KECommon/StaticString.h"
#include "../KECommon/PoolAllocator.h"

#include <cstdio>
#include <chrono>
#include <iostream>
#include <vector>
#include <string>

using namespace std;
using namespace ke;

int main()
{
	StaticStringA helloStaticString = StaticStringA("hello");
	string helloStr = "hello";
	const char* testChar1 = helloStaticString.c_str();
	const char* testChar2 = string("hello").c_str();

	bool test = true;
}