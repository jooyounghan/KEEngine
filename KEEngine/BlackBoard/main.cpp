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
#include <chrono>

#include "OwnedString.h"
#include "StringConvertor.h"
#include "StaticBuffer.h"
#include "ReflectObject.h"
#include "EnumMacro.h"
#include "StaticColumnarArray.h"
#include "Test.h"
#include "HashContainer.h"
#include "File.h"

#include "XmlManager.h"
using namespace std;
using namespace ke;


int main() 
{
    const char* xml = R"(
        <root id="123" name="test">
            <child x="1" y="2">Hello</child>
            <empty-node attr="v" />
        </root>
    )";
}