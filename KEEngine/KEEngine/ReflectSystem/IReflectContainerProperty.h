#pragma once
#include "IReflectProperty.h"

namespace ke
{
	class IReflectObject;

	template <typename Container, typename T>
	concept ReflectContainerCompatible = requires(Container c, const Container cc, std::size_t index)
	{
		{ c.size() } -> std::convertible_to<std::size_t>;
		{ c.resize(index) } -> std::same_as<void>;
		{ c[index] } -> std::convertible_to<T&>;
		{ cc[index] } -> std::convertible_to<const T&>;
	};

	class IReflectContainerProperty : public IReflectProperty
	{
	public:
		IReflectContainerProperty(const FlyweightStringA& name);
		~IReflectContainerProperty() override = default;

	public:
		virtual size_t	size(const IReflectObject* object) const = 0;
		virtual void	resize(IReflectObject* object, size_t newSize) = 0;
	};
}