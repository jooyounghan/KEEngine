#pragma once
#include "FlyweightString.h"

namespace ke
{
	class ReflectMetaData;

	class IReflectObject
	{
	public:
		virtual ~IReflectObject() = default;

	public:
		virtual const ReflectMetaData* getMetaData() const = 0;
		virtual const FlyweightStringA& getName() const = 0;
	};
}