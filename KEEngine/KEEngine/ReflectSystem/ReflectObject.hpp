#pragma region Declare ReflectProperty Macros
#define DECLAR_REFLECT_PROPERTY_METHODS(Type, Variable)							\
	inline static const ke::FlyweightStringA& getName##Variable()				\
	{																			\
		static ke::FlyweightStringA name = ke::FlyweightStringA(#Variable);		\
		return name;															\
	}																			\
	inline Type& get##Variable() { return Variable; }							\
	inline const Type& getConst##Variable() const { return Variable; }			\
	inline void set##Variable(const Type& variable) { Variable = variable; }

#define DECLARE_REFLECT_PROPERTY(Type, Variable)		\
	Type Variable;										\
	DECLAR_REFLECT_PROPERTY_METHODS(Type, Variable);

#define DECLARE_REFLECT_PROPERTY_WITH_DEFAULT(Type, Variable, DefaultValue)	\
	Type Variable = DefaultValue;											\
	DECLAR_REFLECT_PROPERTY_METHODS(Type, Variable);
#pragma endregion

#pragma region Define ReflectProperty Macros
#define BEGIN_DEFINE_REFLECT_PROPERTY(ObjectType)													\
	ke::FlyweightStringA ke::ReflectObject<ObjectType>::_objectName = FlyweightStringA(#ObjectType);\
	ke::ReflectMetaData ke::ReflectObject<ObjectType>::_reflectMetaData = ReflectMetaData(			\
		ke::ReflectObject<ObjectType>::_objectName													\
	); 																								\
	template<> void ke::ReflectObject<ObjectType>::initializeMetaData() {							\
		ke::ReflectMetaData& reflectMetaData = ke::ReflectObject<ObjectType>::_reflectMetaData;

#define DEFINE_REFLECT_PROPERTY_PARAMETER(ObjectType, Variable)	\
	ObjectType::getName##Variable()								\
	, &ObjectType::get##Variable								\
	, &ObjectType::getConst##Variable							\
	, &ObjectType::set##Variable

#define DEFINE_REFLECT_POD_PROPERTY(ObjectType, Variable) { reflectMetaData.addPODProperty(DEFINE_REFLECT_PROPERTY_PARAMETER(ObjectType, Variable)); }
#define DEFINE_REFLECT_ENUM_PROPERTY(ObjectType, Variable) { reflectMetaData.addEnumProperty(DEFINE_REFLECT_PROPERTY_PARAMETER(ObjectType, Variable)); }
#define DEFINE_REFLECT_OBJECT_PROPERTY(ObjectType, Variable) { reflectMetaData.addReflectObjectProperty(DEFINE_REFLECT_PROPERTY_PARAMETER(ObjectType, Variable)); }
#define DEFINE_REFLECT_POD_SEQ_PROPERTY(ObjectType, Variable) { reflectMetaData.addReflectPODSeqProperty(DEFINE_REFLECT_PROPERTY_PARAMETER(ObjectType, Variable)); }
#define DEFINE_REFLECT_OBEJCT_SEQ_PROPERTY(ObjectType, Variable) { reflectMetaData.addReflectObjectSeqProperty(DEFINE_REFLECT_PROPERTY_PARAMETER(ObjectType, Variable)); }

#define END_DEFINE_REFLECT_PROPERTY()	};
#pragma endregion

#pragma region Bind ReflectProperty Macros
#define BEGIN_BIND_REFLECT_PROPERTY(ObjectType)													\
	template<> void ke::ReflectObject<ObjectType>::bindMetaData() {								\
		ke::ReflectMetaData& reflectMetaData = ke::ReflectObject<ObjectType>::_reflectMetaData;

#define BIND_REFLECET_PROPERTY(ObjectType, PropertyType, Variable, UiOption)													\
	{																															\
		IReflectProperty* reflectProperty = reflectMetaData.getPropertyByName(ObjectType::getName##Variable());					\
		KE_ASSERT_ARGS(reflectProperty != nullptr, "Reflect Property not found: %s", ObjectType::getName##Variable().c_str());	\
		reflectProperty->setUIOption(UiOption);																					\
	}

#define BIND_REFLECET_POD_PROPERTY(ObjectType, PropertyType, Variable, UiOption, DefaultValue)									\
	{																															\
		IReflectProperty* reflectProperty = reflectMetaData.getPropertyByName(ObjectType::getName##Variable());					\
		KE_ASSERT_ARGS(reflectProperty != nullptr, "Reflect Property not found: %s", ObjectType::getName##Variable().c_str());	\
		IReflectPODProperty* reflectPODProperty = reflectProperty->castTo<IReflectPODProperty>();								\
		reflectPODProperty->getPODPropertyInfo<PropertyType>()->setDefaultValue(DefaultValue);									\
	}

#define BIND_REFLECET_POD_RANGED_PROPERTY(ObjectType, PropertyType, Variable, UiOption, DefaultValue, MaxValue, MinValue, Step)	\
	{																															\
		IReflectProperty* reflectProperty = reflectMetaData.getPropertyByName(ObjectType::getName##Variable());					\
		KE_ASSERT_ARGS(reflectProperty != nullptr, "Reflect Property not found: %s", ObjectType::getName##Variable().c_str());	\
		IReflectPODProperty* reflectPODProperty = reflectProperty->castTo<IReflectPODProperty>();								\
		ReflectPODPropertyInfo<PropertyType>* reflectPODPropertyInfo = reflectPODProperty->getPODPropertyInfo<PropertyType>();	\
		reflectPODPropertyInfo->setDefaultValue(DefaultValue);																	\
		reflectPODPropertyInfo->assignRangeInfo(MinValue, MaxValue, Step);														\
	}
#define END_BIND_REFLECT_PROPERTY() };

#pragma endregion

#pragma region ReflectObject Macros
#define REFLECT_OBJECT_PREDECLARE(ObjectType)								\
	class ObjectType;														\
	template<> void ke::ReflectObject<ObjectType>::initializeMetaData();	\
	template<> void ke::ReflectObject<ObjectType>::bindMetaData();			\

#define REFLECT_OBJECT_CLASS(ObjectType)									\
	REFLECT_OBJECT_PREDECLARE(ObjectType)									\
	class ObjectType : public ke::ReflectObject<ObjectType>

#define REFLECT_OBJECT_CONSTRUCTOR(ObjectType)		\
ObjectType() : ke::ReflectObject<ObjectType>() {};	\
friend class ke::ReflectObject<ObjectType>;
#pragma endregion

namespace ke
{
	template<typename ObjectType>
	ReflectObject<ObjectType>::ReflectObject()
	{
	}
	
	template<typename ObjectType>
	void ReflectObject<ObjectType>::initializeMetaData()
	{
		STATIC_ASSERT_FUNCTION_NOT_SUPPORTED(ReflectObject);
	}
	
	template<typename ObjectType>
	void ReflectObject<ObjectType>::bindMetaData()
	{
		STATIC_ASSERT_FUNCTION_NOT_SUPPORTED(ReflectObject);
	}

	template<typename ObjectType>
	void ReflectObject<ObjectType>::ensureInitialized()
	{
		KE_MAYBE_UNUSED static const bool isInitialized = (initializeMetaData(), true);
		KE_MAYBE_UNUSED static const bool isBinded = (bindMetaData(), true);
	}

	template<typename ObjectType>
	const ReflectMetaData* ReflectObject<ObjectType>::getObjectMetaData()
	{
		ensureInitialized();
		return &_reflectMetaData;
	}
}