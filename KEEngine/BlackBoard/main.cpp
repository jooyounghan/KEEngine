#include "../KECommon/OwnedString.h"
#include "../KECommon/BoundedString.h"
#include "../KECommon/PoolAllocator.h"
#include "../KECommon/Vector.h"

#include <cstdio>
#include <chrono>
#include <iostream>
#include <vector>
#include <string>

using namespace std;
using namespace ke;

int main()
{
	while (true)
	{
		BoundedStringA<50> helloBoundedString1 = "hello";
		BoundedStringA<50> helloBoundedString2 = BoundedStringA<50>("hello");
		BoundedStringA<50> helloBoundedString3 = helloBoundedString2;

		OwnedStringA helloOwnedString1 = "hello";
		OwnedStringA helloOwnedString2 = OwnedStringA("hello");
		OwnedStringA helloOwnedString3 = helloOwnedString2;

		helloBoundedString1.append(" world ");
		helloBoundedString1.append(helloOwnedString1);
		helloBoundedString1.append(" world ");
		helloBoundedString1.append(helloOwnedString1);
		helloBoundedString1.append(" world ");
		helloBoundedString1.append(helloOwnedString1);
		helloBoundedString1.append(" world\n");
		helloBoundedString1.append("Now");
		helloBoundedString1.append("Bye");
		helloBoundedString1.append("Bye");
		Vector<BoundedStringA<50>> boundedStringVector;
		boundedStringVector.pushBack(helloBoundedString1);
		boundedStringVector.pushBack(helloBoundedString2);
		boundedStringVector.pushBack(helloBoundedString3);

		Vector<OwnedStringA> ownedStringVector;
		ownedStringVector.pushBack(helloOwnedString1);
		ownedStringVector.pushBack(helloOwnedString2);
		ownedStringVector.pushBack(helloOwnedString3);

		bool test = true;
	}
}