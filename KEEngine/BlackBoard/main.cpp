#include "../KECommon/HashConvertor.h"

int main()
{
	ke::uint64 t = ke::HashConvertor::convertToHash("Hello, World!").fold();
	ke::uint64 t3 = ke::HashConvertor::convertToHash("Hello, Younghan!").fold();
	bool test = true;
}