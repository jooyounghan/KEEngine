#pragma once

template<typename T>
class RefObject
{
public:
	explicit RefObject(T& object) : _ptr(&object) {};

private:
	T* _ptr = nullptr;
};