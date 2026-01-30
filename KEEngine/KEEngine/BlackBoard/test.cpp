#include "BlackBoardPch.h"
#include "test.h"

namespace ke
{
	BEGIN_DEFINE_REFLECT_PROPERTY(MoveStatus)
		DEFINE_REFLECT_PROPERTY(MoveStatus, int8, _speed)
		DEFINE_REFLECT_PROPERTY(MoveStatus, float, _slowRatio)
	END_DEFINE_REFLECT_PROPERTY()

	BEGIN_BIND_REFLECT_PROPERTY(MoveStatus)
		BIND_REFLECT_PROPERTY(MoveStatus, int8, _speed, EReflectUIOption::Editable, 0, 100, 1, 10);
		BIND_REFLECT_PROPERTY(MoveStatus, float, _slowRatio, EReflectUIOption::Editable, 0.0f, 1.0f, 0.01f, 0.f);
	END_BIND_REFLECT_PROPERTY()


	BEGIN_DEFINE_REFLECT_PROPERTY(AttackStatus)
		DEFINE_REFLECT_PROPERTY(AttackStatus, int16, _power)
		DEFINE_REFLECT_PROPERTY(AttackStatus, double, _lethality)
	END_DEFINE_REFLECT_PROPERTY()

	BEGIN_BIND_REFLECT_PROPERTY(AttackStatus)
		BIND_REFLECT_PROPERTY(AttackStatus, int16, _power, EReflectUIOption::Editable, 0, 100, 1, 10);
		BIND_REFLECT_PROPERTY(AttackStatus, double, _lethality, EReflectUIOption::Editable, 0.0f, 1.0f, 0.01f, 0.f);
	END_BIND_REFLECT_PROPERTY()

	BEGIN_DEFINE_REFLECT_PROPERTY(CharacterStatus)
		DEFINE_REFLECT_PROPERTY(CharacterStatus, uint32, _killPoint);
		DEFINE_REFLECT_PROPERTY(CharacterStatus, float, _bountyPointRatio);
		DEFINE_REFLECT_PROPERTY(CharacterStatus, MoveStatus, _moveStatus);
		DEFINE_REFLECT_PROPERTY(CharacterStatus, AttackStatus, _attackStatus);
	END_DEFINE_REFLECT_PROPERTY()

	BEGIN_BIND_REFLECT_PROPERTY(CharacterStatus)
		BIND_REFLECT_PROPERTY(CharacterStatus, uint32, _killPoint, EReflectUIOption::Editable, 0, 100, 1, 10);
		BIND_REFLECT_PROPERTY(CharacterStatus, float, _bountyPointRatio, EReflectUIOption::Editable, 0.0f, 1.0f, 0.01f, 0.f);
		BIND_REFLECT_PROPERTY(CharacterStatus, MoveStatus, _moveStatus, EReflectUIOption::Editable);
		BIND_REFLECT_PROPERTY(CharacterStatus, AttackStatus, _attackStatus, EReflectUIOption::Editable);
	END_BIND_REFLECT_PROPERTY()

}