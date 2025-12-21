#pragma once
#include "IReflection.h"
#include "DynamicBuffer.h"

namespace ke
{
	template<typename ObjectType>
	class IReflectionDecriptor
	{
	public:
		virtual IReflection*	getFromObject(ObjectType* reflectObject) = 0;
		virtual void			applyDefaultValue(IReflection* reflection) = 0;
		virtual const void*		getDefaultValue() const = 0;
	};

	template<typename ObjectType, typename PropertyType>
	class ReflectDescriptor : public IReflectionDecriptor<ObjectType>
	{
		using Getter = IReflection* (ObjectType::*)();

	public:
		ReflectDescriptor(const PropertyType& defaultValue, Getter getter);
		virtual ~ReflectDescriptor() = default;

	public:
		virtual void			applyDefaultValue(IReflection* reflection) override;
		virtual const void*		getDefaultValue() const override;

	public:
		IReflection*	getFromObject(ObjectType* reflectObject);

	protected:
		DynamicBuffer _defaultValueBuffer;

	protected:
		Getter _getter;
	};
};
#include "ReflectionDescriptor.hpp"