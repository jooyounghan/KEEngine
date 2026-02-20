#include "BlackBoardPch.h"
#include "test.h"
namespace ke
{
	DEFINE_ENUM_DESCRIPTOR(ECharacterType, Citizen, Warrior, Mage, Archer, Count);

	BEGIN_DEFINE_REFLECT_PROPERTY(MoveStatus)
		DEFINE_REFLECT_POD_PROPERTY(MoveStatus, _speed)
		DEFINE_REFLECT_POD_PROPERTY(MoveStatus, _slowRatio)
	END_DEFINE_REFLECT_PROPERTY()

	BEGIN_BIND_REFLECT_PROPERTY(MoveStatus)
		BIND_REFLECET_POD_RANGED_PROPERTY(MoveStatus, int8, _speed, EReflectUIOption::Editable, 10, 0, 100, 1);
		BIND_REFLECET_POD_RANGED_PROPERTY(MoveStatus, float, _slowRatio, EReflectUIOption::Editable, 0.1f, 0.0f, 1.0f, 0.01f);
	END_BIND_REFLECT_PROPERTY()


	BEGIN_DEFINE_REFLECT_PROPERTY(AttackStatus)
		DEFINE_REFLECT_POD_PROPERTY(AttackStatus, _power)
		DEFINE_REFLECT_POD_PROPERTY(AttackStatus, _lethality)
	END_DEFINE_REFLECT_PROPERTY()

	BEGIN_BIND_REFLECT_PROPERTY(AttackStatus)
		BIND_REFLECET_POD_RANGED_PROPERTY(AttackStatus, int16, _power, EReflectUIOption::Editable, 30, 0, 100, 1);
		BIND_REFLECET_POD_RANGED_PROPERTY(AttackStatus, double, _lethality, EReflectUIOption::Editable, 20.f, 0.0f, 1.0f, 0.01f);
	END_BIND_REFLECT_PROPERTY()

	BEGIN_DEFINE_REFLECT_PROPERTY(CharacterStatus)
		DEFINE_REFLECT_POD_PROPERTY(CharacterStatus, _killPoint);
		DEFINE_REFLECT_POD_PROPERTY(CharacterStatus, _bountyPointRatio);
		DEFINE_REFLECT_OBJECT_PROPERTY(CharacterStatus, _moveStatus);
		DEFINE_REFLECT_OBJECT_PROPERTY(CharacterStatus, _attackStatus);
		DEFINE_REFLECT_ENUM_PROPERTY(CharacterStatus, _characterType);
	END_DEFINE_REFLECT_PROPERTY()

	BEGIN_BIND_REFLECT_PROPERTY(CharacterStatus)
		BIND_REFLECET_POD_RANGED_PROPERTY(CharacterStatus, uint32, _killPoint, EReflectUIOption::Editable, 0, 0, 100, 1);
		BIND_REFLECET_POD_RANGED_PROPERTY(CharacterStatus, float, _bountyPointRatio, EReflectUIOption::Editable, -1.f, 0.0f, 1.0f, 0.01f);
		BIND_REFLECET_PROPERTY(CharacterStatus, MoveStatus, _moveStatus, EReflectUIOption::Editable);
		BIND_REFLECET_PROPERTY(CharacterStatus, AttackStatus, _attackStatus, EReflectUIOption::Editable);
		//BIND_REFLECET_POD_PROPERTY(CharacterStatus, ECharacterType, _characterType, EReflectUIOption::Editable, ECharacterType::Citizen);
	END_BIND_REFLECT_PROPERTY()

}