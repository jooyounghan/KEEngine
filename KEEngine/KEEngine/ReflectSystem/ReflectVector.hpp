#pragma once
#include "ReflectVector.h"

namespace ke
{
	template<typename PropertyType>
	const void* IReflectVectorProperty<PropertyType>::getTypeId() const
	{
		return IReflectStaticTypeId::getStaticTypeId<PropertyType>();
	}


	template<typename ObjectType, typename PropertyType>
	ReflectVectorProperty<ObjectType, PropertyType>::ReflectVectorProperty(
		const FlyweightStringA& name
		, Getter<ObjectType, std::vector<PropertyType>> getter
		, ConstGetter<ObjectType, std::vector<PropertyType>> constGetter
		, Setter<ObjectType, std::vector<PropertyType>> setter
	)
		: ReflectPropertyBase<ObjectType, std::vector<PropertyType>>(name, getter, constGetter, setter)
	{
	}


	template<typename ObjectType, typename PropertyType>
	void ReflectVectorProperty<ObjectType, PropertyType>::setFromBianry(IReflectObject* object, const void* src)
	{
		// Implementation depends on how binary serialization should work for vectors
		// For now, use a simple approach
		ReflectParser::parseFromBinary(src, &this->get(object));
	}

	template<typename ObjectType, typename PropertyType>
	void ReflectVectorProperty<ObjectType, PropertyType>::getToBinary(const IReflectObject* object, IBuffer* outDst) const
	{
		ReflectParser::parseToBinary(outDst, &this->get(object));
	}

	template<typename ObjectType, typename PropertyType>
	void ReflectVectorProperty<ObjectType, PropertyType>::setFromString(IReflectObject* object, const char* src, size_t strlen)
	{
		ReflectParser::parseFromString(src, strlen, &this->get(object));
	}

	template<typename ObjectType, typename PropertyType>
	void ReflectVectorProperty<ObjectType, PropertyType>::getToString(const IReflectObject* object, IBuffer* outStringBuffer) const
	{
		ReflectParser::parseToString(outStringBuffer, &this->get(object));
	}

	template<typename T>
	struct ReflectCastHelper<IReflectVectorProperty<T>>
	{
		static IReflectVectorProperty<T>* cast(IReflectProperty* prop)
		{
			if (prop && prop->getPropertyType() == EReflectPropertyType::Vector)
			{
				return static_cast<IReflectVectorProperty<T>*>(prop->getInterface());
			}
			return nullptr;
		}
		static const IReflectVectorProperty<T>* cast(const IReflectProperty* prop)
		{
			if (prop && prop->getPropertyType() == EReflectPropertyType::Vector)
			{
				return static_cast<IReflectVectorProperty<T>*>(prop->getInterface());
			}
			return nullptr;
		}
	};
}
