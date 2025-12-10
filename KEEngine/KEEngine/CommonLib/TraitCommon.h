#pragma once
#include "pch.h"
#include <type_traits>

#define CHECK_INTEGER_TYPE(T) static_assert(std::is_integral_v<T>, "T must be an integer type.");

#define CHECK_IS_BASE_OF(Base, Derived) static_assert(std::is_base_of_v<Base, Derived>, #Derived " must be derived from " #Base);