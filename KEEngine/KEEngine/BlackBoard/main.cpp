#include "File.h"
#include "FlyweightString.h"
int main()
{
	ke::ReadOnlyFile test("./test.xml");
	ke::FlyweightStringA test1("Hello World");
	ke::FlyweightStringA test2("Hello World1");
	ke::FlyweightStringA test3("Hello World2");
	ke::FlyweightStringA test4("Hello World3");
	ke::FlyweightStringA test5("Hello World4");
	ke::FlyweightStringA test6("Hello World5");
	ke::FlyweightStringA test7("Hello World");
	return 0;
}