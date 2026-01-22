#pragma once
namespace ke
{
	struct XMLAttribute
	{
	public:
		XMLAttribute(const char* pos);

	public:
		std::string_view getName() const;
		std::string_view getValue() const;		
		XMLAttribute getNextAttribute() const;

		inline bool isValid() const { return _currentPos != nullptr; }

	private:
		const char* _currentPos = nullptr;

	private:
		const char* _nameStart = nullptr;
		size_t		_nameLength = INVALID_INDEX(size_t);
		const char* _valueStart = nullptr;
		size_t		_valueLength = INVALID_INDEX(size_t);
	};
}