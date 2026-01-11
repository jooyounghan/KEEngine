
#pragma region Reflect Property Macros
// Declare Reflect Property Macros
#define BEGIN_DECLARE_REFLECT_PROPERTY() 

#define DECLARE_REFLECT_PROPERTY(Type, Variable)								\
private:																		\
	Type Variable;																\
public:																			\
	inline static const ke::FlyweightStringA& getName##Variable()				\
	{																			\
		static ke::FlyweightStringA name = ke::FlyweightStringA(#Variable);		\
		return name;															\
	}																			\
	inline Type& get##Variable() { return Variable; }							\
	inline const Type& getConst##Variable() const { return Variable; }			\
	inline void set##Variable(const Type& variable) { Variable = variable; }

#define END_DECLARE_REFLECT_PROPERTY()

// Define Reflect Property Macros
#define BEGIN_DEFINE_REFLECT_PROPERTY(ObjectType)													\
	ke::FlyweightStringA ke::ReflectObject<ObjectType>::_objectName = FlyweightStringA(#ObjectType);\
	ke::ReflectMetaData ke::ReflectObject<ObjectType>::_reflectMetaData = ReflectMetaData(			\
		ke::ReflectObject<ObjectType>::_objectName													\
	); 																								\
	template<> void ke::ReflectObject<ObjectType>::initializeMetaData() {							\
		ke::ReflectMetaData& reflectMetaData = ke::ReflectObject<ObjectType>::_reflectMetaData;

#define DEFINE_REFLECT_PROPERTY(ObjectType, PropertyType, Variable)	\
	{																\
		reflectMetaData.addProperty(								\
			ObjectType::getName##Variable()							\
			, &ObjectType::get##Variable							\
			, &ObjectType::getConst##Variable						\
			, &ObjectType::set##Variable							\
		);															\
	}

#define END_DEFINE_REFLECT_PROPERTY()	};
#pragma endregion

#pragma region Reflect Object Macros
#define REFLECT_OBJECT_CLASS(ObjectType)								\
	class ObjectType;													\
	template<> void ke::ReflectObject<ObjectType>::initializeMetaData();\
	class ObjectType : public ke::ReflectObject<ObjectType>
#pragma endregion

namespace ke
{
	template<typename ObjectType>
	ReflectObject<ObjectType>::ReflectObject()
	{
	}
	
	template<typename ObjectType>
	void ke::ReflectObject<ObjectType>::initializeMetaData()
	{
		STATIC_ASSERT_FUNCTION_NOT_SUPPORTED(ReflectObject);
	}
	
	template<typename ObjectType>
	void ReflectObject<ObjectType>::ensureInitialized()
	{
		KE_MAYBE_UNUSED static const bool once = (initializeMetaData(), true);
	}

	template<typename ObjectType>
	const ReflectMetaData& ReflectObject<ObjectType>::getObjectMetaData()
	{
		ensureInitialized();
		return _reflectMetaData;
	}
	
	template<typename ObjectType>
	const ReflectMetaData& ReflectObject<ObjectType>::getMetaData() const
	{
		return getObjectMetaData();
	}
}