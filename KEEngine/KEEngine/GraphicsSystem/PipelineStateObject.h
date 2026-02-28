#pragma once
#include "ReflectObject.h"
#include "EnumUtil.h"

namespace ke
{
	enum class EPipelineStateKey
	{
		UseDepthTest,
		UseDepthWrite,
		BlendOpaque,
		BlendAlpha,
		CullBack,
	};

	KE_REFLECT_OBJECT_CLASS(PipelineStateObject)
	{
	public:
		KE_REFLECT_OBJECT_CONSTRUCTOR(PipelineStateObject);
	};
}

