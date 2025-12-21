#pragma once
#include "ReflectObject.h"

#define BEGIN_DEFINE_REFLECT_PROPERTY(ObjectType)										\
	ke::ReflectMetaData<ObjectType> ke::ReflectObject<ObjectType>::_reflectMetaData; 	\
	template<> void ke::ReflectObject<ObjectType>::initializeMetaData() {				\
		ke::ReflectMetaData<ObjectType>& reflectMetaData = ke::ReflectObject<ObjectType>::_reflectMetaData;

#define DEFINE_REFLECT_PROPERTY(ObjectType, PropertyType, VariableName, DefaultValue, Description)	\
	{																								\
		reflectMetaData.registerReflectionDescirptor<PropertyType>(									\
			#VariableName,																			\
			DefaultValue,																			\
			&ObjectType::getReflect##VariableName													\
		);																							\
	}

#define END_DEFINE_REFLECT_PROPERTY(ObjectType)	}

#define DECLARE_REFLECT_PROPERTY(Type, VariableName)												\
private:																							\
	ke::ReflectProperty<Type>	_##VariableName = ke::ReflectProperty<Type>(#VariableName);			\
	inline IReflection* getReflect##VariableName() { return &_##VariableName; }						\
public:																								\
	inline static ke::FlyweightStringA getName##VariableName = #VariableName;						\
	inline const Type& get##VariableName() const { return _##VariableName.getReflectProperty(); }	\
	inline void set##VariableName(const Type& v) { _##VariableName.setReflectProperty(v); }			

#define DECLARE_REFLECT_OBJECT(ObjectType) template<> void ke::ReflectObject<ObjectType>::initializeMetaData()

#define REFLECT_OBJECT_CLASS(ObjectType)	\
	class ObjectType;						\
	DECLARE_REFLECT_OBJECT(TestObject);		\
	class ObjectType : public ke::ReflectObject<ObjectType>

#define BEGIN_DECLARE_REFLECT_PROPERTY(ObjectType) friend class ke::ReflectObject<TestObject>;
#define REFLECT_OBJECT_CONSTRUCTOR(ObjectName) ReflectObject(#ObjectName, this)
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
	ReflectObject<ObjectType>::ReflectObject(const char* objectName, ObjectType* object)
		: IReflection(objectName), _object(object)
	{
		initialize();
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

	template<typename ObjectType>
	Offset ReflectObject<ObjectType>::setFromString(const char* src)
	{
		Offset totalOffset = 0;
		const std::vector<std::unique_ptr<IReflectionDecriptor<ObjectType>>>& reflectionDescriptorList = getReflectMetaData().getReflectionDescriptorList();
		for (const std::unique_ptr<IReflectionDecriptor<ObjectType>>& descriptor : reflectionDescriptorList)
		{
			IReflection* property = descriptor->getFromObject(_object);
			Offset offset = property->setFromString(src);
			totalOffset += offset;
			src += offset;
		}
		return totalOffset;
	}

	template<typename ObjectType>
	Offset ReflectObject<ObjectType>::setFromBinary(const char* src)
	{
		Offset totalOffset = 0;
		const std::vector<std::unique_ptr<IReflectionDecriptor<ObjectType>>>& reflectionDescriptorList = getReflectMetaData().getReflectionDescriptorList();
		for (const std::unique_ptr<IReflectionDecriptor<ObjectType>>& descriptor : reflectionDescriptorList)
		{
			IReflection* property = descriptor->getFromObject(_object);
			Offset offset = property->setFromString(src);
			totalOffset += offset;
			src += offset;
		}
		return totalOffset;
	}

	template<typename ObjectType>
	void ReflectObject<ObjectType>::getToString(IBuffer* outBuffer) const
	{
		const std::vector<std::unique_ptr<IReflectionDecriptor<ObjectType>>>& reflectionDescriptorList = getReflectMetaData().getReflectionDescriptorList();
		for (const std::unique_ptr<IReflectionDecriptor<ObjectType>>& descriptor : reflectionDescriptorList)
		{
			IReflection* property = descriptor->getFromObject(_object);
			property->getToString(outBuffer);
		}
	}

	template<typename ObjectType>
	void ReflectObject<ObjectType>::getToBinary(IBuffer* outBuffer) const
	{
		const std::vector<std::unique_ptr<IReflectionDecriptor<ObjectType>>>& reflectionDescriptorList = getReflectMetaData().getReflectionDescriptorList();
		for (const std::unique_ptr<IReflectionDecriptor<ObjectType>>& descriptor : reflectionDescriptorList)
		{
			IReflection* property = descriptor->getFromObject(_object);
			property->getToBinary(outBuffer);
		}
	}
}