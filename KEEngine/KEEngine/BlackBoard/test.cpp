#include "BlackBoardPch.h"
#include "test.h"
namespace ke
{
	KE_DEFINE_REFLECT_ENUM(ECharacterType, Citizen, Warrior, Mage, Archer, Count);

	KE_BEGIN_DEFINE_REFLECT_PROPERTY(MoveStatus)
		KE_DEFINE_REFLECT_POD_PROPERTY(MoveStatus, _speed)
		KE_DEFINE_REFLECT_POD_PROPERTY(MoveStatus, _slowRatio)
	KE_END_DEFINE_REFLECT_PROPERTY()

	KE_BEGIN_BIND_REFLECT_PROPERTY(MoveStatus)
		KE_BIND_REFLECET_POD_RANGED_PROPERTY(MoveStatus, int8, _speed, EReflectUIOption::Editable, 10, 0, 100, 1);
		KE_BIND_REFLECET_POD_RANGED_PROPERTY(MoveStatus, float, _slowRatio, EReflectUIOption::Editable, 0.1f, 0.0f, 1.0f, 0.01f);
	KE_END_BIND_REFLECT_PROPERTY()


	KE_BEGIN_DEFINE_REFLECT_PROPERTY(AttackStatus)
		KE_DEFINE_REFLECT_POD_PROPERTY(AttackStatus, _power)
		KE_DEFINE_REFLECT_POD_PROPERTY(AttackStatus, _lethality)
	KE_END_DEFINE_REFLECT_PROPERTY()

	KE_BEGIN_BIND_REFLECT_PROPERTY(AttackStatus)
		KE_BIND_REFLECET_POD_RANGED_PROPERTY(AttackStatus, int16, _power, EReflectUIOption::Editable, 30, 0, 100, 1);
		KE_BIND_REFLECET_POD_RANGED_PROPERTY(AttackStatus, double, _lethality, EReflectUIOption::Editable, 20.f, 0.0f, 1.0f, 0.01f);
	KE_END_BIND_REFLECT_PROPERTY()

	KE_BEGIN_DEFINE_REFLECT_PROPERTY(CharacterStatus)
		KE_DEFINE_REFLECT_POD_PROPERTY(CharacterStatus, _killPoint);
		KE_DEFINE_REFLECT_POD_PROPERTY(CharacterStatus, _bountyPointRatio);
		KE_DEFINE_REFLECT_OBJECT_PROPERTY(CharacterStatus, _moveStatus);
		KE_DEFINE_REFLECT_OBJECT_PROPERTY(CharacterStatus, _attackStatus);
		KE_DEFINE_REFLECT_ENUM_PROPERTY(CharacterStatus, _characterType);
	KE_END_DEFINE_REFLECT_PROPERTY()

	KE_BEGIN_BIND_REFLECT_PROPERTY(CharacterStatus)
		KE_BIND_REFLECET_POD_RANGED_PROPERTY(CharacterStatus, uint32, _killPoint, EReflectUIOption::Editable, 0, 0, 100, 1);
		KE_BIND_REFLECET_POD_RANGED_PROPERTY(CharacterStatus, float, _bountyPointRatio, EReflectUIOption::Editable, -1.f, 0.0f, 1.0f, 0.01f);
		KE_BIND_REFLECET_PROPERTY(CharacterStatus, MoveStatus, _moveStatus, EReflectUIOption::Editable);
		KE_BIND_REFLECET_PROPERTY(CharacterStatus, AttackStatus, _attackStatus, EReflectUIOption::Editable);
		KE_BIND_REFLECT_POD_PROPERTY(CharacterStatus, ECharacterType, _characterType, EReflectUIOption::Editable, ECharacterType::Citizen);
	KE_END_BIND_REFLECT_PROPERTY()

}