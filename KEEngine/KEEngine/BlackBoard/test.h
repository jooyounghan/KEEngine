#pragma once
#include "ReflectObject.h"
#include "ReflectProperty.h"

namespace ke
{
	REFLECT_OBJECT_CLASS(MoveStatus)
	{
	public:
		MoveStatus() : REFLECT_OBJECT_CONSTRUCTOR() {}

	BEGIN_DECLARE_REFLECT_PROPERTY(MoveStatus)
		DECLARE_REFLECT_PROPERTY(int32, _speed);
		DECLARE_REFLECT_PROPERTY(float, _slowRatio);
	END_DECLARE_REFLECT_PROPERTY();
	};

	REFLECT_OBJECT_CLASS(CharacterStatus)
	{
	public:
		CharacterStatus() : REFLECT_OBJECT_CONSTRUCTOR() {}

		BEGIN_DECLARE_REFLECT_PROPERTY(CharacterStatus)
			DECLARE_REFLECT_PROPERTY(MoveStatus, _moveStatus);
			DECLARE_REFLECT_PROPERTY(float, _progress);
		END_DECLARE_REFLECT_PROPERTY();
	};
	
}