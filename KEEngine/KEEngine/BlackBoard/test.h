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

	KE_REFLECT_OBJECT_CLASS(MoveStatus)
	{
	public:
		KE_REFLECT_OBJECT_CONSTRUCTOR(MoveStatus);
		
	public:
		KE_DECLARE_REFLECT_PROPERTY_WITH_DEFAULT(int8, _speed, 10);
		KE_DECLARE_REFLECT_PROPERTY_WITH_DEFAULT(float, _slowRatio, 0.1f);
	};

	KE_REFLECT_OBJECT_CLASS(AttackStatus)
	{
	public:
		KE_REFLECT_OBJECT_CONSTRUCTOR(AttackStatus);

	public:
		KE_DECLARE_REFLECT_PROPERTY_WITH_DEFAULT(int16, _power, 30);
		KE_DECLARE_REFLECT_PROPERTY_WITH_DEFAULT(double, _lethality, 20.f);
	};


	KE_REFLECT_OBJECT_CLASS(CharacterStatus)
	{
	public:
		KE_REFLECT_OBJECT_CONSTRUCTOR(CharacterStatus);

	public:
		KE_DECLARE_REFLECT_PROPERTY_WITH_DEFAULT(uint32, _killPoint, 0);
		KE_DECLARE_REFLECT_PROPERTY_WITH_DEFAULT(float, _bountyPointRatio, -1.f);
		KE_DECLARE_REFLECT_PROPERTY(MoveStatus, _moveStatus);
		KE_DECLARE_REFLECT_PROPERTY(AttackStatus, _attackStatus);
		KE_DECLARE_REFLECT_PROPERTY_WITH_DEFAULT(ECharacterType, _characterType, ECharacterType::Citizen);
	};
	
}