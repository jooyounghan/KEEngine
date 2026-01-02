#pragma once
#include "ReflectObject.h"

#define BEGIN_DEFINE_REFLECT_PROPERTY(ObjectType)										\
	ke::ReflectMetaData<ObjectType> ke::ReflectObject<ObjectType>::_reflectMetaData; 	\
	template<> void ke::ReflectObject<ObjectType>::initializeMetaData() {				\
		ke::ReflectMetaData<ObjectType>& reflectMetaData = ke::ReflectObject<ObjectType>::_reflectMetaData;

#define DEFINE_REFLECT_PROPERTY(ObjectType, PropertyType, VariableName, DefaultValue, Description)	\
	{																								\
		reflectMetaData.registerPropertyMetaData<PropertyType>(										\
			#VariableName,																			\
			DefaultValue,																			\
			&ObjectType::getReflectProperty##VariableName											\
		);																							\
	}

#define END_DEFINE_REFLECT_PROPERTY(ObjectType)	}

#define DECLARE_REFLECT_PROPERTY(Type, VariableName)																			\
private:																														\
	Type VariableName;																										\
	ke::ReflectProperty<Type> reflectProperty##VariableName = ke::ReflectProperty<Type>(#VariableName, &##VariableName);		\
	inline IReflectProperty* getReflectProperty##VariableName() { return &reflectProperty##VariableName; }						\
public:																															\
	inline static ke::FlyweightStringA getName##VariableName = #VariableName;													\
	inline const Type& get##VariableName() const { return VariableName; }														\
	inline void set##VariableName(const Type& v) { VariableName = v; }			

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
	ReflectObject<ObjectType>::ReflectObject(ObjectType* object)
		: _object(object)
	{
	}

	template<typename ObjectType>
	void ReflectObject<ObjectType>::initializeMetaData()
	{
		STATIC_ASSERT_FUNCTION_NOT_SUPPORTED(ReflectObject);
	}

	template<typename ObjectType>
	void ReflectObject<ObjectType>::initialize()
	{
		getReflectMetaData().setDefaultValues(_object);
	}
}