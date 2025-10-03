#pragma once
#include "ReflectObject.h"
#include "TemplateCommon.h"

#define BEGIN_REFLECT_PROPERTY(ObjectType)								\
	ReflectMetaData ReflectObject<ObjectType>::InitializeMetaData() {	\
		ReflectMetaData	reflectMetaData;								

#define END_REFLECT_PROPERTY()										}	

#define DECLARE_REFLECT_PROPERTY(Type, VariableName)										\
private:																					\
	ReflectProperty<Type>	_##VariableName = ReflectProperty<Type>(VariableName)			\
public:																						\
	static FlyweightStringA getName##VariableName = #VariableName;							\
	const Type& get##VariableName() const { return _##VariableName.getReflectProperty(); }	\
	void set##VariableName(const Type& v) { _##VariableName.setReflectProperty(v); }										

#define DEFINE_REFLECT_PROPERTY(Type, VariableName, DefaultValue, Description)							\
	{																									\
		ReflectProperty<Type> tempReflectProperty(#VariableName, DefaultValue);							\
		reflectMetaData.registerProperty(PropertyTypeConvertor<Type>::GetType(), &tempReflectProperty);	\
	}
	

#define DEFINE_REFLECT_RANGE_PROPERTY()

namespace ke
{
	template<typename ObjectType>
	ReflectObject<ObjectType>::ReflectObject(ObjectType* object)
		: _object(object) 
	{
	}

	template<typename ObjectType>
	ReflectMetaData ReflectObject<ObjectType>::InitializeMetaData()
	{
		STATIC_ASSERT_FUNCTION_NOT_SUPPORTED(ReflectObject);
	}

}