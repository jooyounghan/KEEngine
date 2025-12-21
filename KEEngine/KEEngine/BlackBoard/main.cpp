#include "test.h"


int main()
{
	{
		ke::TestObject testObject;

		ke::ReflectProperty<ke::int32> healthProperty = ke::ReflectProperty<ke::int32>(testObject.getNameHealth.c_str());
		bool t = true;
	}

	return 0;
}