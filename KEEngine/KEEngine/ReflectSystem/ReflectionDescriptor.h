#pragma once
#include "IReflection.h"
#include "DynamicBuffer.h"

namespace ke
{
	template<typename ObjectType>
	class IReflectionDecriptor
	{
	public:
		virtual const void* getFromObject(ObjectType* reflectObject) const = 0;
		virtual void		setFromObject(ObjectType* reflectObject, const void* value) = 0;
	};

	template<typename ObjectType, typename PropertyType>
	class ReflectDescriptor : public IReflectionDecriptor<ObjectType>
	{
		using Getter = const PropertyType& (ObjectType::*)() const;
		using Setter = void (ObjectType::*)(const PropertyType&);

	public:
		ReflectDescriptor(Getter getter, Setter setter);
		virtual ~ReflectDescriptor() = default;

	public:
		void		applyDefaultValue(IReflection* reflection);
		const void* getDefaultValue() const;

	public:
		const void* getFromObject(ObjectType* reflectObject) const;
		void		setFromObject(ObjectType* reflectObject, const void* value);

	protected:
		DynamicBuffer _defaultValueBuffer;

	protected:
		Getter _getter;
		Setter _setter;
	};
};
#include "ReflectionDescriptor.hpp"