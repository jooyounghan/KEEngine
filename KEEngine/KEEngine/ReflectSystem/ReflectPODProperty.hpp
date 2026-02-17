#pragma once
namespace ke
{
	template<typename PropertyType>
	 const void* IReflectPODProperty<PropertyType>::getTypeId() const
	{
		return IReflectStaticTypeId::getStaticTypeId<PropertyType>();
	}

	template<typename PropertyType>
	void IReflectPODProperty<PropertyType>::assignRangeInfo(const PropertyType& minValue, const PropertyType& maxValue, const PropertyType& step)
	{
		_rangeInfo = MAKE_PTR(RangedPropertyInfo<PropertyType>);
		_rangeInfo->_minValue = minValue;
		_rangeInfo->_maxValue = maxValue;
		_rangeInfo->_step = step;
	}

	template<typename ObjectType, typename PropertyType>
	ReflectPODProperty<ObjectType, PropertyType>::ReflectPODProperty(
		const FlyweightStringA& name
		, Getter<ObjectType, PropertyType> getter
		, ConstGetter<ObjectType, PropertyType> constGetter
		, Setter<ObjectType, PropertyType> setter
	)
		: ReflectPropertyBase<ObjectType, PropertyType>(name, getter, constGetter, setter)
	{
	}

	template<typename ObjectType, typename PropertyType>
	void ReflectPODProperty<ObjectType, PropertyType>::setFromBianry(IReflectObject* object, const void* src)
	{
		ReflectParser::parseFromBinary(src, &this->get(object));
	}

	template<typename ObjectType, typename PropertyType>
	void ReflectPODProperty<ObjectType, PropertyType>::getToBinary(const IReflectObject* object, IBuffer* outDst) const
	{
		ReflectParser::parseToBinary(outDst, &this->get(object));
	}

	template<typename ObjectType, typename PropertyType>
	void ReflectPODProperty<ObjectType, PropertyType>::setFromString(IReflectObject* object, const char* src, size_t strlen)
	{
		ReflectParser::parseFromString(src, strlen , &this->get(object));
	}

	template<typename ObjectType, typename PropertyType>
	void ReflectPODProperty<ObjectType, PropertyType>::getToString(const IReflectObject* object, IBuffer* outStringBuffer) const
	{
		ReflectParser::parseToString(outStringBuffer, &this->get(object));
	}

	template<typename T>
	struct ReflectCastHelper<IReflectPODProperty<T>>
	{
		static IReflectPODProperty<T>* cast(IReflectProperty* prop)
		{
			if (prop && prop->getPropertyType() == EReflectPropertyType::POD)
			{
				return static_cast<IReflectPODProperty<T>*>(prop->getInterface());
			}
			return nullptr;
		}
		static const IReflectPODProperty<T>* cast(const IReflectProperty* prop)
		{
			if (prop && prop->getPropertyType() == EReflectPropertyType::POD)
			{
				return static_cast<IReflectPODProperty<T>*>(prop->getInterface());
			}
			return nullptr;
		}
	};
}