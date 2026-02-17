#pragma once
namespace ke
{
    template <typename ObjectType, typename PropertyType>
    using Getter = PropertyType & (ObjectType::*)();
    template <typename ObjectType, typename PropertyType>
    using ConstGetter = const PropertyType& (ObjectType::*)() const;
    template <typename ObjectType, typename PropertyType>
    using Setter = void (ObjectType::*)(const PropertyType&);

	template<typename ObjectType, typename PropertyType>
	class ReflectPropertyAccessor
	{
    public:
        ReflectPropertyAccessor(
            Getter<ObjectType, PropertyType> getter,
            ConstGetter<ObjectType, PropertyType> constGetter,
            Setter<ObjectType, PropertyType> setter
        ) : _getter(getter)
            , _constGetter(constGetter)
            , _setter(setter)
        {
		}
		virtual ~ReflectPropertyAccessor() = default;

    public:
        PropertyType&       get(IReflectObject* o) { return (static_cast<ObjectType*>(o)->*_getter)(); }
        const PropertyType& get(const IReflectObject* o) const { return (static_cast<const ObjectType*>(o)->*_constGetter)(); }
        void                set(IReflectObject* o, const PropertyType& v) { (static_cast<ObjectType*>(o)->*_setter)(v); }

    protected:
        Getter<ObjectType, PropertyType>            _getter;
        ConstGetter<ObjectType, PropertyType>       _constGetter;
        Setter<ObjectType, PropertyType>            _setter;
	}
}