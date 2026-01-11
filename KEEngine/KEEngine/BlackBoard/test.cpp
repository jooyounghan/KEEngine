#include "BlackBoardPch.h"
#include "test.h"

namespace ke
{
	BEGIN_DEFINE_REFLECT_PROPERTY(MoveStatus)
		DEFINE_REFLECT_PROPERTY(MoveStatus, int32, _speed)
		DEFINE_REFLECT_PROPERTY(MoveStatus, float, _slowRatio)
	END_DEFINE_REFLECT_PROPERTY()

	BEGIN_BIND_PROPERTY()
//
//	BEGIN_BIND_REFLECT_META_DATA(CharacterStatus)
//		BIND_REFLECT_META_DATA(MoveStatus, _moveStatus, MoveStatus(), "Move Status");
//		BIND_REFLECT_META_DATA(float, _progress, 0.0f, "Progress");
//	END_BIND_REFLECT_META_DATA()
//
//	BEGIN_DEFINE_REFLECT_PROPERTY(CharacterStatus)
//		DEFINE_REFLECT_PROPERTY(MoveStatus, _moveStatus)
//		DEFINE_REFLECT_PROPERTY(float, _progress)
//	END_DEFINE_REFLECT_PROPERTY()
}