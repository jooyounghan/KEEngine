#include "test.h"

namespace ke
{
	BEGIN_DEFINE_REFLECT_PROPERTY(MoveStatus)
		DEFINE_REFLECT_PROPERTY(MoveStatus, int32, _speed, 100, "Speed of the object");
		DEFINE_REFLECT_PROPERTY(MoveStatus, float, _slowRatio, 10.0f, "SlowRatio of the object");
	END_DEFINE_REFLECT_PROPERTY(MoveStatus)

	BEGIN_DEFINE_REFLECT_PROPERTY(CharacterStatus)
		DEFINE_REFLECT_PROPERTY(CharacterStatus, MoveStatus, _moveStatus, MoveStatus(), "Move Status");
		DEFINE_REFLECT_PROPERTY(CharacterStatus, float, _progress, 0.0f, "Progress");
	END_DEFINE_REFLECT_PROPERTY(CharacterStatus)
}