#pragma once
#include "ReflectObject.h"

using namespace ke;


class Test : public ReflectObject<Test>
{
public:
	Test() : REFLECT_OBJECT_CONSTRUCTOR()
	{
	};

public:
	DECLARE_REFLECT_PROPERTY(bool, TestBool);
	DECLARE_REFLECT_PROPERTY(float, MinValue);
	DECLARE_REFLECT_PROPERTY(float, MaxValue);
};

DECLARE_REFLECT_OBJECT(Test);