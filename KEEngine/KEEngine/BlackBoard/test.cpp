#include "test.h"

namespace ke
{
	BEGIN_BIND_REFLECT_META_DATA(MoveStatus)
		BIND_REFLECT_META_DATA(int32, _speed, 100, "Speed of the object");
		BIND_REFLECT_META_DATA(float, _slowRatio, 10.0f, "SlowRatio of the object");
	END_BIND_REFLECT_META_DATA()

	BEGIN_DEFINE_REFLECT_PROPERTY(MoveStatus)
		DEFINE_REFLECT_PROPERTY(int32, _speed)
		DEFINE_REFLECT_PROPERTY(float, _slowRatio)
	END_DEFINE_REFLECT_PROPERTY()

	BEGIN_BIND_REFLECT_META_DATA(CharacterStatus)
		BIND_REFLECT_META_DATA(MoveStatus, _moveStatus, MoveStatus(), "Move Status");
		BIND_REFLECT_META_DATA(float, _progress, 0.0f, "Progress");
	END_BIND_REFLECT_META_DATA()

	BEGIN_DEFINE_REFLECT_PROPERTY(CharacterStatus)
		DEFINE_REFLECT_PROPERTY(MoveStatus, _moveStatus)
		DEFINE_REFLECT_PROPERTY(float, _progress)
	END_DEFINE_REFLECT_PROPERTY()
}