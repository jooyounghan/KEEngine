#pragma once
#include "Vector.h"
#include "FlyweightString.h"

namespace ke
{
	struct XMLAttribute
	{
		FlyweightStringA _name;
		OwnedStringA _value;
	};

	struct XMLToken 
	{
		enum class Type 
		{ 
			Start, 
			End, 
			Empty, 
			Text, 
			Eof 
		} _type = Type::Eof;
		
		FlyweightStringA		_name;
		Vector<XMLAttribute>	_attributes;
		OwnedStringA			_text;
	};
}

