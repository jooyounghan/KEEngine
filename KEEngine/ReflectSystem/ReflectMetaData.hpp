#include "ReflectMetaData.h"
#include "TemplateCommon.h"

namespace ke
{
	template<typename Type>
	EPropertyType PropertyTypeConvertor<Type>::GetType() const
	{
		STATIC_ASSERT_FUNCTION_NOT_SUPPORTED(PropertyTypeGetter);
	};
}