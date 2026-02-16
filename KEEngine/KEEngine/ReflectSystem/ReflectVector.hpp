#pragma once
#include "ReflectVector.h"

namespace ke
{
	template<typename ObjectType, typename ElementType>
	ReflectVectorProperty<ObjectType, ElementType>::ReflectVectorProperty(
		const FlyweightStringA& name
		, Getter<ObjectType, std::vector<ElementType>> getter
		, ConstGetter<ObjectType, std::vector<ElementType>> constGetter
		, Setter<ObjectType, std::vector<ElementType>> setter
	)
		: ReflectPropertyBase<ObjectType, std::vector<ElementType>>(name, getter, constGetter, setter)
	{
	}

	template<typename ObjectType, typename ElementType>
	size_t ReflectVectorProperty<ObjectType, ElementType>::getSize(const IReflectObject* object) const
	{
		return this->get(object).size();
	}

	template<typename ObjectType, typename ElementType>
	void ReflectVectorProperty<ObjectType, ElementType>::resize(IReflectObject* object, size_t newSize)
	{
		this->get(object).resize(newSize);
	}

	template<typename ObjectType, typename ElementType>
	void ReflectVectorProperty<ObjectType, ElementType>::clear(IReflectObject* object)
	{
		this->get(object).clear();
	}

	template<typename ObjectType, typename ElementType>
	void* ReflectVectorProperty<ObjectType, ElementType>::getElement(IReflectObject* object, size_t index)
	{
		std::vector<ElementType>& vec = this->get(object);
		if (index < vec.size())
		{
			return &vec[index];
		}
		return nullptr;
	}

	template<typename ObjectType, typename ElementType>
	const void* ReflectVectorProperty<ObjectType, ElementType>::getElement(const IReflectObject* object, size_t index) const
	{
		const std::vector<ElementType>& vec = this->get(object);
		if (index < vec.size())
		{
			return &vec[index];
		}
		return nullptr;
	}

	template<typename ObjectType, typename ElementType>
	void ReflectVectorProperty<ObjectType, ElementType>::setFromBianry(IReflectObject* object, const void* src)
	{
		// Implementation depends on how binary serialization should work for vectors
		// For now, use a simple approach
		ReflectParser::parseFromBinary(src, &this->get(object));
	}

	template<typename ObjectType, typename ElementType>
	void ReflectVectorProperty<ObjectType, ElementType>::getToBinary(const IReflectObject* object, IBuffer* outDst) const
	{
		ReflectParser::parseToBinary(outDst, &this->get(object));
	}

	template<typename ObjectType, typename ElementType>
	void ReflectVectorProperty<ObjectType, ElementType>::setFromString(IReflectObject* object, const char* src, size_t strlen)
	{
		ReflectParser::parseFromString(src, strlen, &this->get(object));
	}

	template<typename ObjectType, typename ElementType>
	void ReflectVectorProperty<ObjectType, ElementType>::getToString(const IReflectObject* object, IBuffer* outStringBuffer) const
	{
		ReflectParser::parseToString(outStringBuffer, &this->get(object));
	}
}
