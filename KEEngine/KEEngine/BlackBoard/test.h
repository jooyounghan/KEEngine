#pragma once
#include "ReflectObject.h"

namespace ke
{
	enum class ECharacterType : uint8
	{
		Citizen,
		Warrior,
		Mage,
		Archer,
		Count
	};

	REFLECT_OBJECT_CLASS(MoveStatus)
	{
	public:
		REFLECT_OBJECT_CONSTRUCTOR(MoveStatus);
		
	public:
		DECLARE_REFLECT_PROPERTY_WITH_DEFAULT(int8, _speed, 10);
		DECLARE_REFLECT_PROPERTY_WITH_DEFAULT(float, _slowRatio, 0.1f);
	};

	REFLECT_OBJECT_CLASS(AttackStatus)
	{
	public:
		REFLECT_OBJECT_CONSTRUCTOR(AttackStatus);

	public:
		DECLARE_REFLECT_PROPERTY_WITH_DEFAULT(int16, _power, 30);
		DECLARE_REFLECT_PROPERTY_WITH_DEFAULT(double, _lethality, 20.f);
	};


	REFLECT_OBJECT_CLASS(CharacterStatus)
	{
	public:
		REFLECT_OBJECT_CONSTRUCTOR(CharacterStatus);

	public:
		DECLARE_REFLECT_PROPERTY_WITH_DEFAULT(uint32, _killPoint, 0);
		DECLARE_REFLECT_PROPERTY_WITH_DEFAULT(float, _bountyPointRatio, -1.f);
		DECLARE_REFLECT_PROPERTY(MoveStatus, _moveStatus);
		DECLARE_REFLECT_PROPERTY(AttackStatus, _attackStatus);
		DECLARE_REFLECT_PROPERTY(ECharacterType, _characterType);
	};
	
}