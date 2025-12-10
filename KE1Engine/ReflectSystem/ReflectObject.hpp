#pragma once
#include "ReflectObject.h"
#include "TemplateCommon.h"

#define BEGIN_DEFINE_REFLECT_PROPERTY(ObjectType)								\
	ReflectMetaData<ObjectType> ReflectObject<ObjectType>::_metaData; 			\
	template<> void ReflectObject<ObjectType>::initializeMetaData() {			\
		ReflectMetaData<ObjectType>& metaData = ReflectObject<ObjectType>::_metaData;

#define END_DEFINE_REFLECT_PROPERTY(ObjectType)	}

#define DECLARE_REFLECT_OBJECT(ObjectType) template<> void ReflectObject<ObjectType>::initializeMetaData();

#define DECLARE_REFLECT_PROPERTY(Type, VariableName)												\
private:																							\
	ReflectProperty<Type>	_##VariableName = ReflectProperty<Type>(#VariableName);					\
public:																								\
	inline static FlyweightStringA getName##VariableName = #VariableName;							\
	inline const Type& get##VariableName() const { return _##VariableName.getReflectProperty(); }	\
	inline void set##VariableName(const Type& v) { _##VariableName.setReflectProperty(v); }										

#define DEFINE_REFLECT_PROPERTY(ObjectType, PropertyType, VariableName, PropertyFlag, DefaultValue, Description)	\
	{																												\
		metaData.registerProperty<PropertyType>(																	\
			#VariableName,																							\
			PropertyFlag,																							\
			DefaultValue,																							\
			&ObjectType::get##VariableName,																			\
			&ObjectType::set##VariableName																			\
		);																											\
	}

#define DEFINE_REFLECT_RANGE_PROPERTY()

namespace ke
{
	template<typename ObjectType>
	void ReflectObject<ObjectType>::ensureInitialized()
	{
		static const bool once = (initializeMetaData(), true);
		(void)once;
	}

	template<typename ObjectType>
	const ReflectMetaData<ObjectType>& ReflectObject<ObjectType>::getMetaData()
	{
		ensureInitialized();
		return _metaData;
	}

	template<typename ObjectType>
	ReflectObject<ObjectType>::ReflectObject(ObjectType* object)
		: _object(object) 
	{

	}

	template<typename ObjectType>
	void ReflectObject<ObjectType>::initializeMetaData()
	{
		STATIC_ASSERT_FUNCTION_NOT_SUPPORTED(ReflectObject);
	}
}