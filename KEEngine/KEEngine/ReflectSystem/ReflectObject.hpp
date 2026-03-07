#pragma region Declare ReflectProperty Macros
#define KE_DECLARE_REFLECT_PROPERTY_METHODS(Type, Variable)						\
	inline static const ke::FlyweightStringA& getName##Variable()				\
	{																			\
		static ke::FlyweightStringA name = ke::FlyweightStringA(#Variable);		\
		return name;															\
	}																			\
	inline Type& get##Variable() { return Variable; }							\
	inline const Type& getConst##Variable() const { return Variable; }			\
	inline void set##Variable(const Type& variable) { Variable = variable; }

#define KE_DECLARE_REFLECT_PROPERTY(Type, Variable)		\
	Type Variable;										\
	KE_DECLARE_REFLECT_PROPERTY_METHODS(Type, Variable);

#define KE_DECLARE_REFLECT_PROPERTY_WITH_DEFAULT(Type, Variable, DefaultValue)	\
	Type Variable = DefaultValue;												\
	KE_DECLARE_REFLECT_PROPERTY_METHODS(Type, Variable);
#pragma endregion

#pragma region Define ReflectProperty Macros
#define KE_BEGIN_DEFINE_REFLECT_PROPERTY(ObjectType)												\
	ke::FlyweightStringA ke::ReflectObject<ObjectType>::_objectName = FlyweightStringA(#ObjectType);\
	ke::ReflectMetaData ke::ReflectObject<ObjectType>::_reflectMetaData = ReflectMetaData(			\
		ke::ReflectObject<ObjectType>::_objectName													\
	); 																								\
	template<> void ke::ReflectObject<ObjectType>::initializeMetaData() {							\
		ke::ReflectMetaData& reflectMetaData = ke::ReflectObject<ObjectType>::_reflectMetaData;

#define KE_PROPERTY_NAME(ObjectType, Variable) ObjectType::getName##Variable()

#define KE_DEFINE_REFLECT_PROPERTY_PARAMETER(ObjectType, Variable)	\
	&ObjectType::get##Variable,										\
	&ObjectType::getConst##Variable,								\
	&ObjectType::set##Variable

#define KE_DEFINE_REFLECT_PROPERTY(ObjectType, Variable, Uioption) \
{ reflectMetaData.addReflectProperty(KE_PROPERTY_NAME(ObjectType, Variable), Uioption, KE_DEFINE_REFLECT_PROPERTY_PARAMETER(ObjectType, Variable)); }

#define KE_DEFINE_REFLECT_PROPERTY_WITH_DEFAULT(ObjectType, Variable, Uioption, DefaultValue) \
{ reflectMetaData.addReflectProperty(KE_PROPERTY_NAME(ObjectType, Variable), Uioption, KE_DEFINE_REFLECT_PROPERTY_PARAMETER(ObjectType, Variable), DefaultValue); }

#define KE_DEFINE_REFLECT_OBJECT_PROPERTY(ObjectType, Variable, Uioption) \
{ reflectMetaData.addReflectObjectProperty(KE_PROPERTY_NAME(ObjectType, Variable), Uioption, KE_DEFINE_REFLECT_PROPERTY_PARAMETER(ObjectType, Variable)); }

#define KE_DEFINE_REFLECT_SEQUENCE_PROPERTY(ObjectType, Variable, Uioption) \
{ reflectMetaData.addReflectSequenceProperty(KE_PROPERTY_NAME(ObjectType, Variable), Uioption, KE_DEFINE_REFLECT_PROPERTY_PARAMETER(ObjectType, Variable)); }

#define KE_DEFINE_REFLECT_SEQUENCE_PROPERTY_WITH_DEFAULT(ObjectType, Variable, Uioption, DefaultValue) \
{ reflectMetaData.addReflectSequenceProperty(KE_PROPERTY_NAME(ObjectType, Variable), Uioption, KE_DEFINE_REFLECT_PROPERTY_PARAMETER(ObjectType, Variable), DefaultValue); }

#define KE_DEFINE_REFLECT_OBEJCT_SEQUENCE_PROPERTY(ObjectType, Variable, Uioption) \
{ reflectMetaData.addReflectObjectSequenceProperty(KE_PROPERTY_NAME(ObjectType, Variable), Uioption, KE_DEFINE_REFLECT_PROPERTY_PARAMETER(ObjectType, Variable)); }

#define KE_END_DEFINE_REFLECT_PROPERTY()	};
#pragma endregion

#pragma region ReflectObject Macros
#define KE_REFLECT_OBJECT_PREDECLARE(ObjectType)							\
	class ObjectType;														\
	template<> void ke::ReflectObject<ObjectType>::initializeMetaData();	\
	template<> void ke::ReflectObject<ObjectType>::bindMetaData();			\

#define KE_REFLECT_OBJECT_CLASS(ObjectType)									\
	KE_REFLECT_OBJECT_PREDECLARE(ObjectType)								\
	class ObjectType : public ke::ReflectObject<ObjectType>

#define KE_REFLECT_OBJECT_CONSTRUCTOR(ObjectType)	\
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