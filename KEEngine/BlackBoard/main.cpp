#include "../KECommon/DirtyFlaggedFunction.h"
#include "../KECommon/HashConvertor.h"
#include "../KECommon/BitFlag.h"

#include <cstdio>

using namespace ke;

class Test
{
	public:
	void testFunction(int x)
	{
		printf("Test function called with value: %d\n", x);
	}
};

int main()
{
	BitFlag<32> flag;

	flag.setFlag(0);
	flag.setFlag(1);

	DirtyFlaggedFunction<void, int> func([](int x) {
		printf("Function called with value: %d\n", x);
	});

	func.execute(1);
	func.setDirty();
	func.execute(2);
	func.execute(3);

	Test testInstance;
	
	DirtyFlaggedFunction<void, int> memberFunc(BindMember(&testInstance, &Test::testFunction));
	memberFunc.execute(10);
	memberFunc.setDirty();
	memberFunc.execute(20);
	memberFunc.execute(30);

}