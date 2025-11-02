#pragma once
#include "HashMap.h"
#include "ReflectProperty.h"
#include "EnumMacro.h"

namespace ke
{
	DECLARE_ENUM_CLASS(
		EPropertyType, 
		uint8,
		None,
		Boolean,
		Int8,
		Int16,
		Int32,
		Int64,
		UInt8,
		UInt16,
		UInt32,
		UInt64,
		Float,
		Double,
		String,
		Count
	);
	
	DECLARE_ENUM_CLASS(
		EPropertyFlag,
		uint8,
		None,
		ReadOnly,
		WriteOnly,
		ReadWrite
	);

	template<typename Type>
	struct PropertyTypeConvertor
	{
		static EPropertyType GetType();
	};

	template<typename ObjectType>
	class ReflectObject;

	template<typename ObjectType>
	class PropertyMetaData
	{
	public:
		~PropertyMetaData() 
		{ 
			if (_contextDestroier != nullptr)
			{
				_contextDestroier(_context);
				_contextDestroier = nullptr;
			}
		}

	private:
		EPropertyType										_propertyType = EPropertyType::None;
		void*												_context = nullptr;
		StaticBuffer<KEConstant::kPropertyBinaryBufferSize> _defaultValueBuffer;

		using DestroyContext = void (*)(void* ctx);
		using PropertyGetter = const void* (*)(ObjectType* reflectObject, void* ctx);
		using PropertySetter = void (*)(ObjectType* reflectObject, const void* value, void* ctx);

		DestroyContext										_contextDestroier = nullptr;
		PropertyGetter										_propertyGetter = nullptr;
		PropertySetter										_propertySetter = nullptr;

	public:
		EPropertyFlag getPropertyFlag() const { return _propertyType; }

	public:
		const void* getPropertyFromObject(ObjectType* reflectObject) const { return _propertyGetter(reflectObject, _context); };
		void setPropertyFromObject(ObjectType* reflectObject, const void* value) { _propertySetter(reflectObject, value, _context); };
		
	public:
		template<typename PropertyType>
		using PropertyGetterFromObject = const PropertyType& (ObjectType::*)() const;
		template<typename PropertyType>
		using PropertySetterFromObject = void (ObjectType::*)(const PropertyType&);
		template<typename PropertyType>
		static PropertyMetaData createPropertyMetaData(
			EPropertyType							type,
			const PropertyType&						defaultPropertyValue,
			PropertyGetterFromObject<PropertyType>	getterFromObject,
			PropertySetterFromObject<PropertyType>	setterFromObject
		);
	};

	template<typename ObjectType, typename PropertyType>
	struct MemberAccessContext
	{
		using Getter = const PropertyType& (ObjectType::*)() const;
		using Setter = void (ObjectType::*)(const PropertyType&);

		Getter _getter;
		Setter _setter;
	};

	template<typename ObjectType>
	template<typename PropertyType>
	PropertyMetaData<ObjectType> PropertyMetaData<ObjectType>::createPropertyMetaData(
		EPropertyType							type, 
		const PropertyType&						defaultPropertyValue, 
		PropertyGetterFromObject<PropertyType>	getterFromObject, 
		PropertySetterFromObject<PropertyType>	setterFromObject
	)
	{
		PropertyMetaData<ObjectType> propertyMetaData;

		propertyMetaData._propertyType = type;
		ReflectParser::parseToBinary(&propertyMetaData._defaultValueBuffer, defaultPropertyValue);

		MemberAccessContext<ObjectType, PropertyType>* context = new MemberAccessContext<ObjectType, PropertyType>();
		context->_getter = getterFromObject;
		context->_setter = setterFromObject;

		propertyMetaData._context = context;

		propertyMetaData._contextDestroier = [](void* ctx)
			{
				// 현재 문제가 되는건 propertyMetaData가 복사될때 context가 복사될 때 함수 포인터가 복사되면서 소멸자가 두번 호출되는 문제
				// 복사를 막거나 이동 생성자를 만들어서 해결해야함
				// 추가로 propertyMetaDataMap에 insert될때도 복사가 일어나므로 이부분도 해결해야함

				MemberAccessContext<ObjectType, PropertyType>* contextPtr = static_cast<MemberAccessContext<ObjectType, PropertyType>*>(ctx);
				delete contextPtr;
			};

		propertyMetaData._propertyGetter = [](ObjectType* reflectObject, void* ctx)
			{
				MemberAccessContext<ObjectType, PropertyType>* contextPtr = static_cast<MemberAccessContext<ObjectType, PropertyType>*>(ctx);
				const PropertyType& ref = (reflectObject->*(contextPtr->_getter))();
				return static_cast<const void*>(&ref);
			};

		propertyMetaData._propertySetter = [](ObjectType* reflectObject, const void* value, void* ctx)
			{
				MemberAccessContext<ObjectType, PropertyType>* contextPtr = static_cast<MemberAccessContext<ObjectType, PropertyType>*>(ctx);
				const PropertyType* propertyPtr = static_cast<const PropertyType*>(value);
				(reflectObject->*(contextPtr->_setter))(*propertyPtr);
			};

		return propertyMetaData;
	}

	template<typename ObjectType>
	class ReflectMetaData
	{
	public:
		ReflectMetaData() = default;
		NONCOPYABLE(ReflectMetaData);

	public:
		CompactBinHoodHashMap<FlyweightStringA, PropertyMetaData<ObjectType>> _propertyMetaDataMap;

	public:
		void registerProperty(const FlyweightStringA& propertyName, PropertyMetaData<ObjectType> propertyMetaData);
	
	public:
		void setDefaultValue(IReflectProperty* property) const;
	};


}

#include "ReflectMetaData.hpp"