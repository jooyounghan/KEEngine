#pragma once
#include "ReflectObject.h"

namespace ke
{
	REFLECT_OBJECT_CLASS(MoveStatus)
	{
	public:
		REFLECT_OBJECT_CONSTRUCTOR(MoveStatus);
		
	public:
		DECLARE_REFLECT_PROPERTY(int8, _speed);
		DECLARE_REFLECT_PROPERTY(float, _slowRatio);
	};

	REFLECT_OBJECT_CLASS(AttackStatus)
	{
	public:
		REFLECT_OBJECT_CONSTRUCTOR(AttackStatus);

	public:
		DECLARE_REFLECT_PROPERTY(int16, _power);
		DECLARE_REFLECT_PROPERTY(double, _lethality);
	};


	REFLECT_OBJECT_CLASS(CharacterStatus)
	{
	public:
		REFLECT_OBJECT_CONSTRUCTOR(CharacterStatus);

	public:
		DECLARE_REFLECT_PROPERTY(uint32, _killPoint);
		DECLARE_REFLECT_PROPERTY(float, _bountyPointRatio);
		DECLARE_REFLECT_PROPERTY(MoveStatus, _moveStatus);
		DECLARE_REFLECT_PROPERTY(AttackStatus, _attackStatus);
	};
	
}