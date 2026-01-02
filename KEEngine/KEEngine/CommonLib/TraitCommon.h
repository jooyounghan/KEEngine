#pragma once
#include "CommonLibPch.h"
#include <type_traits>

#define IS_INTEGER_TYPE(T) std::is_integral_v<T>
#define STATIC_ASSERT_INTEGER_TYPE(T) static_assert(IS_INTEGER_TYPE(T), "T must be an integer type.");

#define IS_BASE_OF(Base, Derived) std::is_base_of_v<Base, Derived>
#define STATIC_ASSERT_IS_BASE_OF(Base, Derived) static_assert(IS_BASE_OF(Base, Derived), #Derived " must be derived from " #Base);