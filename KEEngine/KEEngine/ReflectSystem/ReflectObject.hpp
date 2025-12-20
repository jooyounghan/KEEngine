#pragma once
#include "ReflectObject.h"

#define BEGIN_DEFINE_REFLECT_PROPERTY(ObjectType)								\
	ke::ReflectObject<ObjectType> ke::ReflectObject<ObjectType>::_metaData; 	\
	template<> void ke::ReflectObject<ObjectType>::initializeMetaData() {		\
		ke::ReflectMetaData<ObjectType>& reflectMetaData = ke::ReflectMetaData<ObjectType>::_reflectMetaData;

#define END_DEFINE_REFLECT_PROPERTY(ObjectType)	}

#define DECLARE_REFLECT_PROPERTY(Type, VariableName)												\
private:																							\
	ke::ReflectProperty<Type>	_##VariableName = ke::ReflectProperty<Type>(#VariableName);			\
public:																								\
	inline static ke::FlyweightStringA getName##VariableName = #VariableName;						\
	inline const Type& get##VariableName() const { return _##VariableName.getReflectProperty(); }	\
	inline void set##VariableName(const Type& v) { _##VariableName.setReflectProperty(v); }										

#define DEFINE_REFLECT_PROPERTY(ObjectType, PropertyType, VariableName, DefaultValue, Description)	\
	{																								\
		reflectMetaData.registerReflectionDescirptor<PropertyType>(									\
			#VariableName,																			\
			DefaultValue,																			\
			&ObjectType::get##VariableName,															\
			&ObjectType::set##VariableName															\
		);																							\
	}

#define DECLARE_REFLECT_OBJECT(ObjectType) template<> void ke::ReflectObject<ObjectType>::initializeMetaData()

#define REFLECT_OBJECT_CLASS(ObjectType)	\
	class ObjectType;						\
	DECLARE_REFLECT_OBJECT(TestObject);		\
	class ObjectType : public ke::ReflectObject<ObjectType>

#define REFLECT_OBJECT_CONSTRUCTOR() ReflectObject(this)


namespace ke
{
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
	ReflectObject<ObjectType>::ReflectObject(const char* objectName, ObjectType* object)
		: IReflection(objectName), _object(object)
	{

	}

	template<typename ObjectType>
	void ReflectObject<ObjectType>::initializeMetaData()
	{
		STATIC_ASSERT_FUNCTION_NOT_SUPPORTED(ReflectObject);
	}
}