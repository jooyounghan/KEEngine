#include "../KECommon/DirtyFlaggedFunction.h"
#include "../KECommon/HashConvertor.h"
#include "../KECommon/BitFlag.h"

#include <cstdio>

using namespace ke;

class Test
{
	public:
	int testFunction(int x)
	{
		printf("Test function called with value: %d\n", x);
		return x;
	}
};

int main()
{
	BitFlag<32> flag;

	OptionalValue<int> optValue1(OptionalValue<int>(10));
	OptionalValue<int> optValue2 = move(optValue1);
	int index = 5;

}