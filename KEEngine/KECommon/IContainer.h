#pragma once
#include "TypeCommon.h"

template<typename T, typename Alloc>
class IConatiner
{
public:
	virtual ~IConatiner() = default;
	virtual void PushBack(KE_IN const T& element) = 0;
	virtual void PushBack(KE_IN T&& element) = 0;
	virtual void PopBack(KE_OUT T* elementOut) = 0;
};