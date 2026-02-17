namespace ke
{
	template<typename ObjectType, typename PropertyType>
	ReflectObjectProperty<ObjectType, PropertyType>::ReflectObjectProperty(
		const FlyweightStringA& name
		, Getter<ObjectType, PropertyType> getter
		, ConstGetter<ObjectType, PropertyType> constGetter
		, Setter<ObjectType, PropertyType> setter
	)
		: ReflectPropertyBase<ObjectType, PropertyType>(name, getter, constGetter, setter)
	{
		STATIC_ASSERT_IS_BASE_OF(IReflectObject, PropertyType);
	}

#define ERROR_REFLECT_OBJECT_METHOD_NOT_ALLOWED(methodName, description) \
    KE_ASSERT(false, "ReflectObjectProperty::" #methodName               \
                     " is not allowed. (" #description ")")

#define ERROR_REFLECT_OBJECT_SERIALIZE_NOT_ALLOWED(methodName) \
	ERROR_REFLECT_OBJECT_METHOD_NOT_ALLOWED(methodName, "Serialize/Deserialize is not allowed for ReflectObjectProperty.")

	template<typename ObjectType, typename PropertyType>
	void ReflectObjectProperty<ObjectType, PropertyType>::setFromBianry(IReflectObject* object, const void* src)
	{
		ERROR_REFLECT_OBJECT_SERIALIZE_NOT_ALLOWED(setFromBianry);
	}

	template<typename ObjectType, typename PropertyType>
	void ReflectObjectProperty<ObjectType, PropertyType>::getToBinary(const IReflectObject* object, IBuffer* outDst) const
	{
		ERROR_REFLECT_OBJECT_SERIALIZE_NOT_ALLOWED(getToBinary);
	}

	template<typename ObjectType, typename PropertyType>
	void ReflectObjectProperty<ObjectType, PropertyType>::setFromString(IReflectObject* object, const char* src, size_t strlen)
	{
		ERROR_REFLECT_OBJECT_SERIALIZE_NOT_ALLOWED(setFromString);
	}

	template<typename ObjectType, typename PropertyType>
	void ReflectObjectProperty<ObjectType, PropertyType>::getToString(const IReflectObject* object, IBuffer* outStringBuffer) const
	{
		ERROR_REFLECT_OBJECT_SERIALIZE_NOT_ALLOWED(getToString);
	}

	template<>
	struct ReflectCastHelper<IReflectObjectProperty>
	{
		static IReflectObjectProperty* cast(IReflectProperty* prop)
		{
			if (prop && prop->getPropertyType() == EReflectPropertyType::Object)
				return static_cast<IReflectObjectProperty*>(prop->getInterface());
			return nullptr;
		}
		static const IReflectObjectProperty* cast(const IReflectProperty* prop)
		{
			if (prop && prop->getPropertyType() == EReflectPropertyType::Object)
				return static_cast<const IReflectObjectProperty*>(prop->getInterface());
			return nullptr;
		}
	};
}