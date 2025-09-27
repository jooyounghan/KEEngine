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
#include "ReflectMetaData.h"
#include "EnumMacro.h"

using namespace ke;

DEFINE_ENUM_CLASS_WITH_STRINGS(Test, None, Count);

int main() {
    const Vector<OwnedStringA>& t = TestString;
    bool test;
}