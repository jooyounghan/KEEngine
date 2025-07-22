#include "../KECommon/DirtyBitFlaggedFunction.h"
#include "../KECommon/HashConvertor.h"
#include "../KECommon/BitFlag.h"
#include "../KECommon/StaticString.h"
#include "../KECommon/Vector.h"
#include "../KECommon/RingBuffer.h"
#include "../KECommon/OverwriteRingBuffer.h"

#include <cstdio>
#include <chrono>
#include <iostream>
#include <vector>

using namespace std;
using namespace ke;

class LogTest
{
public:
	LogTest() { }
	LogTest(const LogTest&) {  }
	LogTest(LogTest&&) {  }
};

int main()
{
	vector<LogTest> stdVector;	
	Vector<LogTest> manualVector;
	RingBuffer<LogTest, 5> ringBuffer;
	OverwriteRingBuffer<LogTest, 5> overwriteRingBuffer;
	LogTest t = LogTest();

	auto start = std::chrono::high_resolution_clock::now();
	
	for (uint64 idx = 0; idx < 100000; ++idx)
	{
		manualVector.pushBack(t);
	}
	std::chrono::duration<double, std::milli> duration_ms1 = std::chrono::high_resolution_clock::now() - start;
	std::cout << "Manual Vector " << duration_ms1.count() << " ms\n";

	start = std::chrono::high_resolution_clock::now();

	for (uint64 idx = 0; idx < 100000; ++idx)
	{
		stdVector.push_back(t);
	}
	std::chrono::duration<double, std::milli> duration_ms2 = std::chrono::high_resolution_clock::now() - start;
	std::cout << "Std Vector " << duration_ms2.count() << " ms\n";

}