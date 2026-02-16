#pragma once
#include "IReflectProperty.h"

namespace ke
{
	class IReflectVectorProperty
	{
	public:
		virtual ~IReflectVectorProperty() = default;

	public:
		virtual size_t getSize(const IReflectObject* object) const = 0;
		virtual void resize(IReflectObject* object, size_t newSize) = 0;
		virtual void clear(IReflectObject* object) = 0;
		
		// Methods to access elements (can be extended as needed)
		virtual void* getElement(IReflectObject* object, size_t index) = 0;
		virtual const void* getElement(const IReflectObject* object, size_t index) const = 0;
	};
}
