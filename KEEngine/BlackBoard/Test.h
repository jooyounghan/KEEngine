#pragma once
#include "ReflectObject.h"

using namespace ke;

class Test : public ReflectObject<Test>
{
public:
	Test() : REFLECT_OBJECT_CONSTRUCTOR() {};



};