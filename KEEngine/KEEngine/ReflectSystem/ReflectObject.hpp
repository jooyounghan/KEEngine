#pragma once
#include "ReflectObject.h"

#define BEGIN_BIND_REFLECT_META_DATA(ObjectType)										\
	ke::ReflectMetaData<ObjectType> ke::ReflectObject<ObjectType>::_reflectMetaData; 	\
	template<> void ke::ReflectObject<ObjectType>::initializeMetaData() {				\
		ke::ReflectMetaData<ObjectType>& reflectMetaData = ke::ReflectObject<ObjectType>::_reflectMetaData;

#define BIND_REFLECT_META_DATA(PropertyType, VariableName, DefaultValue, Description)	\
	{																					\
		reflectMetaData.registerPropertyMetaData<PropertyType>(							\
			#VariableName,																\
			DefaultValue																\
		);																				\
	}

#define END_BIND_REFLECT_META_DATA()	};

#define DECLARE_REFLECT_PROPERTY(Type, VariableName)																			\
private:																														\
	Type VariableName;																											\
public:																															\
	inline static ke::FlyweightStringA getName##VariableName = #VariableName;													\
	inline const Type& get##VariableName() const { return VariableName; }														\

#define BEGIN_DEFINE_REFLECT_PROPERTY(ObjectType) template<> void ke::ReflectObject<ObjectType>::initializeProperties() {	

#define DEFINE_REFLECT_PROPERTY(PropertyType, VariableName)										\
	{																							\
		registerProperty<PropertyType>(_object->getName##VariableName, &_object->VariableName);	\
	}

#define END_DEFINE_REFLECT_PROPERTY()	};

#define DECLARE_REFLECT_OBJECT(ObjectType) template<> void ke::ReflectObject<ObjectType>::initializeMetaData()

#define REFLECT_OBJECT_CLASS(ObjectType)	\
	class ObjectType;						\
	DECLARE_REFLECT_OBJECT(ObjectType);		\
	class ObjectType : public ke::ReflectObject<ObjectType>

#define BEGIN_DECLARE_REFLECT_PROPERTY(ObjectType) friend class ke::ReflectObject<ObjectType>;
#define REFLECT_OBJECT_CONSTRUCTOR() ReflectObject(this)
#define END_DECLARE_REFLECT_PROPERTY()

namespace ke
{
	template<typename ObjectType>
	void ReflectObject<ObjectType>::initializeMetaData()
	{
		STATIC_ASSERT_FUNCTION_NOT_SUPPORTED(ReflectObject);
	}

	template<typename ObjectType>
	void ReflectObject<ObjectType>::ensureInitialized()
	{
		static const bool once = (initializeMetaData(), true);
		(void)once;
	}

	template<typename ObjectType>
	const ReflectMetaData<ObjectType>& ReflectObject<ObjectType>::getReflectMetaData()
	{
		ensureInitialized();
		return _reflectMetaData;
	}

	template<typename ObjectType>
	void ReflectObject<ObjectType>::initializeProperties()
	{
		STATIC_ASSERT_FUNCTION_NOT_SUPPORTED(ReflectObject);
	}

	template<typename ObjectType>
	template<typename PropertyType, typename ...Args>
	void ReflectObject<ObjectType>::registerProperty(FlyweightStringA propertyName, Args ...args)
	{
		if (_reflectPropertyIndexMap.find(propertyName) != _reflectPropertyIndexMap.end())
		{
			KE_DEBUG_ASSERT(false, "PropertyMetaData already registered in ReflectMetaData.");
		}
		else
		{
			uint32 propertyIndex = static_cast<uint32>(_reflectPropertyList.size());
			_reflectPropertyIndexMap.emplace(propertyName, propertyIndex);
			_reflectPropertyList.push_back(std::make_unique<ReflectProperty<PropertyType>>(propertyName, args...));
		}

	}

	template<typename ObjectType>
	ReflectObject<ObjectType>::ReflectObject(ObjectType* object)
		: _object(object)
	{
	}

	template<typename ObjectType>
	void ReflectObject<ObjectType>::initialize()
	{
		initializeProperties();

		const ReflectMetaData<ObjectType>& reflectMetaData = getReflectMetaData();
		for (size_t i = 0; i < _reflectPropertyList.size(); ++i)
		{
			IReflectProperty* reflectProperty = _reflectPropertyList[i].get();
			const std::unique_ptr<IPropertyMetaData<ObjectType>>& propertyMetaData = reflectMetaData._propertyMetaDataList[i];
			
			if (propertyMetaData)
			{
				propertyMetaData->applyDefaultValue(reflectProperty);
				reflectProperty->setIsDefaultProperty(true);
			}
		}
	}
}