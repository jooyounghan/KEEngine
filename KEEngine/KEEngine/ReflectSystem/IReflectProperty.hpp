namespace ke
{
    template<typename T>
    inline T* ReflectCastHelper<T>::cast(IReflectProperty* prop)
    {
        STATIC_ASSERT_FUNCTION_NOT_SUPPORTED(ReflectCastHelper);
    }

    template<typename T>
    inline const T* ReflectCastHelper<T>::cast(const IReflectProperty* prop)
    {
        STATIC_ASSERT_FUNCTION_NOT_SUPPORTED(ReflectCastHelper);
    }

    template<typename T>
    T* IReflectProperty::castTo()
    {
        return ReflectCastHelper<T>::cast(this);
    }

    template<typename T>
    const T* IReflectProperty::castTo() const
    {
        return ReflectCastHelper<T>::cast(this);
    }
}