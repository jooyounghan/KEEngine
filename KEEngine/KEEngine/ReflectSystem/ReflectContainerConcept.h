#pragma once
namespace ke
{
	class IReflectObject;

	template <typename Container, typename T>
	concept ReflectSequenceContainerCompatible = std::ranges::range<Container> && requires(Container c, const Container cc, std::size_t index, T& val, const T& cval)
	{
		{ c.size() } -> std::convertible_to<std::size_t>;

		{ c.push_back(val) } -> std::same_as<void>;
		{ c.push_back(std::move(val)) } -> std::same_as<void>;

		{ c.emplace_back() } -> std::same_as<T&>;
		{ c.emplace_back(std::move(val)) } -> std::same_as<T&>;

		{ c[index] } -> std::convertible_to<T&>;
		{ cc[index] } -> std::convertible_to<const T&>;
	};

	template <typename Container, typename KeyType, typename ValueType>
	concept ReflectKeyValueContainerCompatible = requires(Container c, const Container cc, std::size_t index, KeyType & key, const KeyType & constKey, ValueType & value, const ValueType & constValue)
	{
		{ c.size() } -> std::convertible_to<std::size_t>;

		{ c.find(key) } -> std::same_as<typename Container::iterator>;
		{ cc.find(key) } -> std::same_as<typename Container::const_iterator>;
		{ c.end() } -> std::same_as<typename Container::iterator>;
		{ cc.end() } -> std::same_as<typename Container::const_iterator>;

		{ c[key] } -> std::convertible_to<ValueType&>;

		{ c.emplace(key, value) } -> std::convertible_to<std::pair<typename Container::iterator, bool>>;
	};
}